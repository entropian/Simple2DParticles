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
	bool show_another_window = false;
	ImVec4 clear_color = ImColor(114, 114, 154);

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
		
		{	// GUI code
			if (ImGui::CollapsingHeader("Particle Emitters"))
			{
				std::vector<float> positions;
				positions.resize(p_emitters.size() * 2);
				std::vector<float> vel_modifiers;
				vel_modifiers.resize(p_emitters.size());
				std::vector<float> emit_rates;
				emit_rates.resize(p_emitters.size());
				for (int i = 0; i < p_emitters.size(); i++)
				{
					positions[2 * i] = p_emitters[i].getX();
					positions[2 * i + 1] = p_emitters[i].getY();
					ImGui::TextWrapped("Emitter %d", i);
					std::string pos_name("Position " + std::to_string(i));
					if (ImGui::DragFloat2(pos_name.c_str(), &(positions[2 * i]), 0.003, 0.0f, 1.0f))
					{
						p_emitters[i].setX(positions[2 * i]);
						p_emitters[i].setY(positions[2 * i + 1]);
					}
					vel_modifiers[i] = p_emitters[i].getVelocityModifier();
					std::string vel_name("Velocity " + std::to_string(i));
					if (ImGui::DragFloat(vel_name.c_str(), &(vel_modifiers[i]), 0.0001, 0.0f, 1.0f))
					{
						p_emitters[i].setVelocityModifier(vel_modifiers[i]);
					}
					emit_rates[i] = p_emitters[i].getParticlesPerSec();
					std::string emit_name("Rate " + std::to_string(i));
					if (ImGui::DragFloat(emit_name.c_str(), &(emit_rates[i]), 2.0f, 0.0f, 10000.0f))
					{
						p_emitters[i].setParticlesPerSec(emit_rates[i]);
					}
					if (ImGui::Button("Delete"))
					{
						p_emitters.erase(p_emitters.begin() + i);
					}
				}
				if (ImGui::Button("Add particle emitter"))
				{
					p_emitters.push_back(ParticleEmitter());
				}
			}

			if (ImGui::CollapsingHeader("Forces"))
			{
				// Display modifiable data:
				// For Gravity: position, force modifier
				// For Wind: direction, force modifier
			}
		}
		if(show_test_window)
		{
			ImGui::SetNextWindowPos(ImVec2(650, 20), ImGuiSetCond_FirstUseEver);
			ImGui::ShowTestWindow(&show_test_window);
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
