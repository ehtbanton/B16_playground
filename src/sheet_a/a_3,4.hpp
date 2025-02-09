/*
Question 3

a) Encapsulation is crucial for OOP. It is the concept of hiding complex implementation details from the user (a black box), 
and only revealing a set of basic interface functions and classes. It also involves the complete separation of modules, so 
that their interdependencies are very easy to track.

b) Compile-time polymorphism is also known as method overloading. It is a feature of C++ which allows multiple functions to 
have the same name but take different arguments. Could be useful e.g. if you need to define functions to perform calcs on 
complex number objects in a similar way to how you would with built-in types.

c) Inheritance is a mechanism by which a class gains some methods and properties from a parent class. This can help with 
code reusability - for example, if I have a vehicle class, I could create child classes car and bike which inherit shared 
methods like move() and stop() from the parent class.


Question 4
See below.

Class Mass contains the mass, position, velocity and acceleration of a physical mass object. It has a method update_mass().
Class Spring contains the spring constant, rest length and damping constant of a physical spring object. It has a method force_exerted().
Classes Mass and Spring are implemented INDEPENDENTLY of each other. They are then gathered in the World class.
The World class has a method update() which calculates the spring force and updates the masses' positions. It also has getters for the positions.

*/


#include <iostream>
#include <chrono>
#include <thread>



class Mass { // It's a physical mass object not the physical mass of an object
private:
	double mass;
	double position;
	double velocity;
	double acceleration;

public:

	Mass(double mass, double position, double velocity, double acceleration) {
		this->mass = mass;
		this->position = position;
		this->velocity = velocity;
		this->acceleration = acceleration;
	}

	void update_mass(double force_experienced, double dt) {
		acceleration = force_experienced / mass;
		velocity += acceleration * dt;
		position += velocity * dt;
	}

	double get_position() {
		return position;
	}

	double get_velocity() {
		return velocity;
	}

};



class Spring {
private:
	double spring_constant;
	double rest_length;
	double damping_constant;

public:

	Spring(double spring_constant, double rest_length, double damping_constant) {
		this->spring_constant = spring_constant;
		this->rest_length = rest_length;
		this->damping_constant = damping_constant;
	}

	double force_exerted(double pos1, double vel1, double pos2, double vel2) {
		double distance = pos2 - pos1;
		double relative_velocity = vel2 - vel1;
		double force = spring_constant * (distance - rest_length) + damping_constant * relative_velocity;
		return force;  // force on mass1, force on mass2 will be opposite(!)
	}
};



class World{
private:
	// Instantiate the mass and spring objects
	Mass mass1;
	Mass mass2;
	Spring spring;

public:
	World(double m1 = 1.0, double p1 = 0.0, double v1 = 0.0,
		  double m2 = 1.0, double p2 = 10.0, double v2 = 0.0,
		  double k = 1.0, double rest = 10.0, double damp = 1.0)
		// ...and pass the parameters to the constructors
		: mass1(m1, p1, v1, 0.0),
		  mass2(m2, p2, v2, 0.0),
		  spring(k, rest, damp) {
	}

	void update(double dt) {
		// Calculate spring force
		double force = spring.force_exerted(
			mass1.get_position(), mass1.get_velocity(),
			mass2.get_position(), mass2.get_velocity()
		);

		// Update masses (equal and opposite forces)
		mass1.update_mass(force, dt);
		mass2.update_mass(-force, dt);  // opposite force on mass2
	}

	// Getters for positions
	double get_mass1_position() { return mass1.get_position(); }
	double get_mass2_position() { return mass2.get_position(); }
};



// For visualisation...
void render_line(double pos1, double pos2, int width = 100) {
	// Scale positions to fit the terminal width
	const int scaled_pos1 = static_cast<int>((pos1 / 15.0) * width);
	const int scaled_pos2 = static_cast<int>((pos2 / 15.0) * width);

	std::string line(width, ' ');

	// Draw spring
	for (int i = std::min(scaled_pos1, scaled_pos2);
		i <= std::max(scaled_pos1, scaled_pos2); i++) {
		if (i >= 0 && i < width) {
			line[i] = '-';
		}
	}

	// Draw masses
	if (scaled_pos1 >= 0 && scaled_pos1 < width) {
		line[scaled_pos1] = 'O';
	}
	if (scaled_pos2 >= 0 && scaled_pos2 < width) {
		line[scaled_pos2] = 'O';
	}

	std::cout << "\033[2J\033[H";  // Clear screen
	std::cout << line << '\n';
}






inline void q4_mass_spring_sim() {
	// Create world with two masses and a spring
	World world(
		1.0, 0.0, 2.0,    // mass1: mass, position, velocity
		0.5, 7.0, 0.0,   // mass2: mass, position, velocity
		5, 5.0, 0.2    // spring: k, rest_length, damping
	);

	// Simulation loop
	double dt = 0.01;
	for (int i = 0; i < 1000; i++) {
		world.update(dt);

		// Get positions and render visualization
		double pos1 = world.get_mass1_position();
		double pos2 = world.get_mass2_position();
		render_line(pos1, pos2);

		std::cout << "Mass1 pos: " << pos1
			<< "\nMass2 pos: " << pos2 << std::endl;

		std::this_thread::sleep_for(std::chrono::milliseconds(10));
	}
}