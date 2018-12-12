#include "imgui/imgui.h"
#include "imgui/imgui_impl_glfw_gl3.h"

#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include "simulation.h"
#include <cstdlib>
#include <cmath>
#include <iostream>
#include "gl/glcode.h"
#include "canvas.h"
#include "util.h"
#include <string>




Simulation::Simulation(const int max_particles, const float brightness_modifier)
    :brightness_modifier(brightness_modifier), p_emitter(), damping(0.8f), particles(max_particles)
{
 //   srand(0);
 //   std::vector<Particle>::iterator itr;
	//for(auto& p : particles)
 //   {
	//	float x = float(rand()) / float(RAND_MAX);
	//	float y = float(rand()) / float(RAND_MAX);
	//	particles.push_back(p);
 //   }
}

Simulation::~Simulation()
{

}

void Simulation::addForceGravity(Gravity& g)
{
    Gravity* gravity = new Gravity();
    *gravity = g;
    forces.push_back(reinterpret_cast<ForceEmitter*>(gravity));
}

void Simulation::addForceWind(Wind& w)
{
    Wind* wind = new Wind();
    *wind = w;
    forces.push_back(reinterpret_cast<ForceEmitter*>(wind));
}

void Simulation::addParticleEmitter(const float x, const float y, const float p_per_sec,
	const float vel_modifier)
{
	p_emitters.push_back(ParticleEmitter(x, y, p_per_sec, vel_modifier));
}

static const double display_time_interval = 1.0;

void Simulation::run(Canvas* canvas, Viewport* viewport)

{
	bool show_test_window = true;

	const double display_time_interval = 1.0;
	double prev_time = glfwGetTime();
	double last_display_time = prev_time;
	bool running = true;

	while (running)
	{
		ImGui_ImplGlfwGL3_NewFrame();
		
		/*{
			auto f = 0.0f;
			ImGui::Text("Hellow, world!");
			ImGui::SliderFloat("float", &f, 0.0f, 1.0f);
			ImGui::ColorEdit3("clear color", (float*)&clear_color);
			if (ImGui::Button("Test Window")) show_test_window ^= 1;
			if (ImGui::Button("Another Window")) show_another_window ^= 1;
			ImGui::Text("Application average &.3f ms/frame (%.1f FPS)",
				1000.0f / ImGui::GetIO().Framerate, ImGui::GetIO().Framerate);
		}*/

		if (show_test_window)
		{
			ImGui::SetNextWindowPos(ImVec2(650, 20), ImGuiSetCond_FirstUseEver);
			ImGui::ShowTestWindow(&show_test_window);
		}
		
		{	// GUI code
			if (ImGui::CollapsingHeader("Particle Emitters"))
			{
				for (int i = 0; i < p_emitters.size(); i++)
				{
					ImGui::PushID(i);
					float pos[2] = { p_emitters[i].getX(), p_emitters[i].getY() };
					ImGui::Text("Emitter");
					if (ImGui::DragFloat2("Position", pos, 0.003, 0.0f, 1.0f))
					{
						p_emitters[i].setX(pos[0]);
						p_emitters[i].setY(pos[1]);
					}
					float vel = p_emitters[i].getVelocityModifier();
					if (ImGui::DragFloat("Velocity", &vel, 0.0001, 0.0f, 1.0f))
					{
						p_emitters[i].setVelocityModifier(vel);
					}
					float emit_rate = p_emitters[i].getParticlesPerSec();
					if (ImGui::DragFloat("Rate", &emit_rate, 2.0f, 0.0f, 10000.0f))
					{
						p_emitters[i].setParticlesPerSec(emit_rate);
					}
					if (ImGui::Button("Delete"))
					{
						p_emitters.erase(p_emitters.begin() + i);
					}
					ImGui::PopID();
				}
				if (ImGui::Button("Add particle emitter"))
				{
					p_emitters.push_back(ParticleEmitter());
				}
			}

			if (ImGui::CollapsingHeader("Forces"))
			{
				for (int i = 0; i < forces.size(); i++)
				{
					ImGui::PushID(i);
					switch (forces[i]->getType())
					{
					case ForceType::GRAVITY: {
						ImGui::Text("Gravity");
						Gravity *gravity = reinterpret_cast<Gravity*>(forces[i]);
						float pos[2] = { gravity->getCenterX(), gravity->getCenterY() };
						if (ImGui::DragFloat2("Position", pos, 0.003, 0.0f, 1.0f))
						{
							gravity->setCenterX(pos[0]);
							gravity->setCenterY(pos[1]);
						}
						float radius = gravity->getRadius();
						if (ImGui::DragFloat("Radius", &radius, 0.001f, 0.0f, 0.5f))
						{
							gravity->setRadius(radius);
						}
						float G = gravity->getG();
						if (ImGui::DragFloat("G", &G, 0.0005f, 0.0f, 1.0f))
						{
							gravity->setG(G);
						}
					} break;
					case ForceType::WIND: {
						ImGui::Text("Wind");
						Wind *wind = reinterpret_cast<Wind*>(forces[i]);
						float dir[2] = { wind->getX(), wind->getY() };
						if (ImGui::DragFloat2("Direction", dir, 0.001f, -1.0f, 1.0f))
						{
							wind->setX(dir[0]);
							wind->setY(dir[1]);
						}
						float magnitude = wind->getMagnitude();
						if (ImGui::DragFloat("Magnitude", &magnitude, 0.001, 0.0f, 1.0f))
						{
							wind->setMagnitude(magnitude);
						}
					} break;
					}
					if (ImGui::Button("Delete"))
					{
						forces.erase(forces.begin() + i);
					}
					ImGui::PopID();
				}
				static bool adding_force = false;
				static ForceType type = ForceType::NONE;
				if (!adding_force)
				{
					if (ImGui::Button("Add new force"))
						adding_force = true;
				}
				else
				{
					if (type == ForceType::NONE)
					{
						if (ImGui::Button("Gravity"))
							type = ForceType::GRAVITY;
						if (ImGui::Button("Wind"))
							type == ForceType::WIND;
						if (ImGui::Button("Cancel"))
						{
							adding_force = false;
						}
					}
					else if (type == ForceType::GRAVITY)
					{
						Gravity *gravity = new Gravity();
						forces.push_back(reinterpret_cast<ForceEmitter*>(gravity));
						adding_force = false;
						type = ForceType::NONE;
					}
					else if (type == ForceType::WIND)
					{
						Wind *wind = new Wind();
						forces.push_back(reinterpret_cast<ForceEmitter*>(wind));
						adding_force = false;
						type = ForceType::NONE;
					}
				}
			}
		}
		
		double current_time = glfwGetTime();
		float delta_t = float(current_time - prev_time);
		update(delta_t);
		canvas->prepDrawing(delta_t);
		draw(canvas);
		viewport->displayImage(canvas->getCanvasData(), canvas->getWidth(), canvas->getHeight());
		if (current_time - last_display_time >= display_time_interval)
		{
			std::cout << 1.0f / delta_t << " FPS\n";
			last_display_time = current_time;
		}
		glfwPollEvents();
		prev_time = current_time;
	}
}

void Simulation::dampenParticle(Particle& p, const float delta_t)
{
    float px = p.getX();
    float py = p.getY();
    float vx = p.getVx();
    float vy = p.getVy();
    const float dampened = 1.0f - ((1.0f - damping) * delta_t);
    vx *= 1.0f - ((1.0f - damping) * delta_t);
    vy *= 1.0f - ((1.0f - damping) * delta_t);
    p.setVx(vx);
    p.setVy(vy);    
}

void Simulation::applyForces(Particle& p, const float delta_t)
{
    float force_x = 0.0f, force_y = 0.0f;
	for(auto& f : forces)
	{
		float fx, fy;
		f->calcForce(fx, fy, p, delta_t);
		force_x += fx;
		force_y += fy;
	}
    p.setVx(p.getVx() + force_x);
    p.setVy(p.getVy() + force_y);
	auto force_mag = sqrtf(force_x * force_x + force_y * force_y);
	p.setForceMag(force_mag);
}

void Simulation::emitParticles(const float delta_t)
{
	for (auto &pe : p_emitters)
	{
		std::vector<Particle> new_particles;
		pe.emit(new_particles, delta_t);
		particles.insert(particles.end(), new_particles.begin(), new_particles.end());
	}
}

void Simulation::updateForces(const float delta_t)
{
	for (auto& f : forces)
	{
		f->update(delta_t);
	}
}

void Simulation::update(const float delta_t)
{    
	updateForces(delta_t);
    std::vector<Particle>::iterator itr;
	for(auto& p : particles)
    {
        dampenParticle(p, delta_t); // NOTE: moving this out of Gravity noticeably lowered FPS
                                       // inline?
        applyForces(p, delta_t);
		p.updatePosition(delta_t);
    }
	emitParticles(delta_t);
}

void Simulation::draw(Canvas* canvas)
{
    std::vector<Particle>::iterator itr;
	for(auto& p : particles)
    {  
		/*
        canvas->drawParticle(p.getX(), p.getY(),
                         clamp(0.1 / p.getDistToCOG(), 0.0f, 0.8f) * brightness_modifier,
                         0.5f * brightness_modifier,
                         clamp((1.0 - 0.1 / p.getDistToCOG()), 0.0f, 1.0f) * brightness_modifier);
						 */
		canvas->drawParticle(p.getX(), p.getY(),
			clamp(sqrtf(p.getForceMag()) * 40.0f, 0.0f, 1.0f) * brightness_modifier,
			0.5f * brightness_modifier,
			clamp(1.0f - sqrtf(p.getForceMag()) * 40.0f, 0.0f, 0.8f) * brightness_modifier);
    }
	canvas->calcImage();
}
