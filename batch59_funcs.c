#include "shell.h"

/* Batch 59: Scientific Instruments, Simulation & Digital Twin (40 commands) */

static void cmd_gazebo59(int argc, char args[][CMD_MAX_LEN]) {
    if (argc < 2) {
        vga_puts("Usage: gazebo <start|stop|status|spawn|step|reset>\n");
        return;
    }
    if (strcmp(args[1], "start") == 0) {
        vga_set_color(VGA_LIGHT_GREEN, VGA_BLACK);
        vga_puts("[Gazebo] Robot simulator engine starting...\n");
        vga_puts("[Gazebo] Loading SDF world: empty_world.sdf\n");
        vga_puts("[Gazebo] Physics: ODE solver, dt=1ms, RTF=1.0\n");
        vga_set_color(VGA_WHITE, VGA_BLACK);
        vga_puts("[Gazebo] Simulation started. Port 11345, 247 topics.\n");
    } else if (strcmp(args[1], "spawn") == 0) {
        vga_set_color(VGA_LIGHT_CYAN, VGA_BLACK);
        vga_puts("[Gazebo] Spawning pioneer3dx at (0,0,0.1)\n");
        vga_puts("[Gazebo] Links: 8, Joints: 7, Sensors: 3\n");
        vga_set_color(VGA_WHITE, VGA_BLACK);
    } else if (strcmp(args[1], "step") == 0) {
        vga_set_color(VGA_LIGHT_GREY, VGA_BLACK);
        vga_puts("[Gazebo] Physics step: 1ms, contacts: 3, forces: 42\n");
        vga_set_color(VGA_WHITE, VGA_BLACK);
    } else if (strcmp(args[1], "stop") == 0) {
        vga_set_color(VGA_YELLOW, VGA_BLACK);
        vga_puts("[Gazebo] Simulation stopped. Total: 342.5s\n");
        vga_set_color(VGA_WHITE, VGA_BLACK);
    } else if (strcmp(args[1], "status") == 0) {
        vga_set_color(VGA_LIGHT_CYAN, VGA_BLACK);
        vga_puts("[Gazebo] RUNNING | Models: 4 | Sensors: 12 | FPS: 60\n");
        vga_set_color(VGA_WHITE, VGA_BLACK);
    } else if (strcmp(args[1], "reset") == 0) {
        vga_set_color(VGA_LIGHT_GREEN, VGA_BLACK);
        vga_puts("[Gazebo] World reset to initial state.\n");
        vga_set_color(VGA_WHITE, VGA_BLACK);
    } else {
        vga_puts("Usage: gazebo <start|stop|status|spawn|step|reset>\n");
    }
}static void cmd_webots59(int argc, char args[][CMD_MAX_LEN]) {
    if (argc < 2) {
        vga_puts("Usage: webots <load|run|pause|step|supervisor|robotinfo>\n");
        return;
    }
    if (strcmp(args[1], "load") == 0) {
        vga_set_color(VGA_LIGHT_GREEN, VGA_BLACK);
        vga_puts("[Webots] Loading world: robot_arena.wbt\n");
        vga_puts("[Webots] Env: 10x10m, walls: 12, robots: 6\n");
        vga_puts("[Webots] Physics: ODE, gravity=-9.81, ERP=0.8\n");
        vga_set_color(VGA_WHITE, VGA_BLACK);
    } else if (strcmp(args[1], "run") == 0) {
        vga_set_color(VGA_LIGHT_CYAN, VGA_BLACK);
        vga_puts("[Webots] Running real-time. ts=32ms, 6 controllers\n");
        vga_set_color(VGA_WHITE, VGA_BLACK);
    } else if (strcmp(args[1], "step") == 0) {
        vga_set_color(VGA_LIGHT_GREY, VGA_BLACK);
        vga_puts("[Webots] Step 32ms: motors=12, sensors=36, coll=1\n");
        vga_set_color(VGA_WHITE, VGA_BLACK);
    } else if (strcmp(args[1], "pause") == 0) {
        vga_set_color(VGA_YELLOW, VGA_BLACK);
        vga_puts("[Webots] Paused at t=45.2s.\n");
        vga_set_color(VGA_WHITE, VGA_BLACK);
    } else if (strcmp(args[1], "supervisor") == 0) {
        vga_set_color(VGA_LIGHT_MAGENTA, VGA_BLACK);
        vga_puts("[Webots] Supervisor: 6 robots, goals=3, resets=0\n");
        vga_set_color(VGA_WHITE, VGA_BLACK);
    } else if (strcmp(args[1], "robotinfo") == 0) {
        vga_set_color(VGA_LIGHT_CYAN, VGA_BLACK);
        vga_puts("[Webots] e-puck: bat=92%, 8 dist | turtlebot: bat=85%\n");
        vga_set_color(VGA_WHITE, VGA_BLACK);
    } else {
        vga_puts("Usage: webots <load|run|pause|step|supervisor|robotinfo>\n");
    }
}

static void cmd_mujoco59(int argc, char args[][CMD_MAX_LEN]) {
    if (argc < 2) {
        vga_puts("Usage: mujoco <load|simulate|forward|inverse|contacts|energy>\n");
        return;
    }
    if (strcmp(args[1], "load") == 0) {
        vga_set_color(VGA_LIGHT_GREEN, VGA_BLACK);
        vga_puts("[MuJoCo] Loading humanoid.xml: 14 bodies, 12 joints\n");
        vga_puts("[MuJoCo] Solver: PGS, iter=50, tol=1e-8\n");
        vga_set_color(VGA_WHITE, VGA_BLACK);
    } else if (strcmp(args[1], "simulate") == 0) {
        vga_set_color(VGA_LIGHT_CYAN, VGA_BLACK);
        vga_puts("[MuJoCo] Forward dynamics: dt=2ms, Euler, 1200x RT\n");
        vga_set_color(VGA_WHITE, VGA_BLACK);
        vga_puts("[MuJoCo] Contacts: avg=45.2N, max=312.8N\n");
    } else if (strcmp(args[1], "forward") == 0) {
        vga_set_color(VGA_LIGHT_GREY, VGA_BLACK);
        vga_puts("[MuJoCo] FK: EE=(0.45,0.12,0.89), COM=(0.01,0,0.92)\n");
        vga_set_color(VGA_WHITE, VGA_BLACK);
    } else if (strcmp(args[1], "inverse") == 0) {
        vga_set_color(VGA_LIGHT_CYAN, VGA_BLACK);
        vga_puts("[MuJoCo] IK: target=(0.5,0,1), Newton, 12 iters\n");
        vga_set_color(VGA_WHITE, VGA_BLACK);
    } else if (strcmp(args[1], "contacts") == 0) {
        vga_set_color(VGA_LIGHT_GREEN, VGA_BLACK);
        vga_puts("[MuJoCo] 3 contacts: foot_L=340N, foot_R=280N, hand=15N\n");
        vga_set_color(VGA_WHITE, VGA_BLACK);
    } else if (strcmp(args[1], "energy") == 0) {
        vga_set_color(VGA_YELLOW, VGA_BLACK);
        vga_puts("[MuJoCo] KE=45.2J, PE=892.1J, eff=93.4%\n");
        vga_set_color(VGA_WHITE, VGA_BLACK);
    } else {
        vga_puts("Usage: mujoco <load|simulate|forward|inverse|contacts|energy>\n");
    }
}

static void cmd_pybullet59(int argc, char args[][CMD_MAX_LEN]) {
    if (argc < 2) {
        vga_puts("Usage: pybullet <connect|load|step|debug|restitution|dynamics>\n");
        return;
    }
    if (strcmp(args[1], "connect") == 0) {
        vga_set_color(VGA_LIGHT_GREEN, VGA_BLACK);
        vga_puts("[PyBullet] Connected to Bullet 3.25, GUI mode\n");
        vga_puts("[PyBullet] Gravity: (0,0,-9.81), dt: 1/240\n");
        vga_set_color(VGA_WHITE, VGA_BLACK);
    } else if (strcmp(args[1], "load") == 0) {
        vga_set_color(VGA_LIGHT_CYAN, VGA_BLACK);
        vga_puts("[PyBullet] URDF: kuka_iiwa, 9 links, 7 revolute joints\n");
        vga_set_color(VGA_WHITE, VGA_BLACK);
    } else if (strcmp(args[1], "step") == 0) {
        vga_set_color(VGA_LIGHT_GREY, VGA_BLACK);
        vga_puts("[PyBullet] Step 1/240s: pairs=15, contacts=4\n");
        vga_set_color(VGA_WHITE, VGA_BLACK);
    } else if (strcmp(args[1], "debug") == 0) {
        vga_set_color(VGA_LIGHT_CYAN, VGA_BLACK);
        vga_puts("[PyBullet] Debug viz: 12 drawn, 3 text, 5 sliders\n");
        vga_set_color(VGA_WHITE, VGA_BLACK);
    } else if (strcmp(args[1], "restitution") == 0) {
        vga_set_color(VGA_YELLOW, VGA_BLACK);
        vga_puts("[PyBullet] Steel=0.82, Rubber=0.91, Plastic=0.45\n");
        vga_set_color(VGA_WHITE, VGA_BLACK);
    } else if (strcmp(args[1], "dynamics") == 0) {
        vga_set_color(VGA_LIGHT_GREEN, VGA_BLACK);
        vga_puts("[PyBullet] Damp=0.5, Stiff=240, Friction=0.9, MaxF=240Nm\n");
        vga_set_color(VGA_WHITE, VGA_BLACK);
    } else {
        vga_puts("Usage: pybullet <connect|load|step|debug|restitution|dynamics>\n");
    }
}

static void cmd_bullet59(int argc, char args[][CMD_MAX_LEN]) {
    if (argc < 2) {
        vga_puts("Usage: bullet <init|rigidbody|softbody|constraint|collision|raycast>\n");
        return;
    }
    if (strcmp(args[1], "init") == 0) {
        vga_set_color(VGA_LIGHT_GREEN, VGA_BLACK);
        vga_puts("[Bullet] Bullet 3.25: DBVT broadphase, SI solver, dt=1/60\n");
        vga_set_color(VGA_WHITE, VGA_BLACK);
    } else if (strcmp(args[1], "rigidbody") == 0) {
        vga_set_color(VGA_LIGHT_CYAN, VGA_BLACK);
        vga_puts("[Bullet] 3 bodies: box(1kg), sphere(0.5kg), plane(static)\n");
        vga_set_color(VGA_WHITE, VGA_BLACK);
    } else if (strcmp(args[1], "softbody") == 0) {
        vga_set_color(VGA_LIGHT_MAGENTA, VGA_BLACK);
        vga_puts("[Bullet] Cloth 32x32: mass=1kg, 1089 vertices\n");
        vga_set_color(VGA_WHITE, VGA_BLACK);
    } else if (strcmp(args[1], "constraint") == 0) {
        vga_set_color(VGA_YELLOW, VGA_BLACK);
        vga_puts("[Bullet] P2P constraint + Hinge motor [-1.57, 1.57]\n");
        vga_set_color(VGA_WHITE, VGA_BLACK);
    } else if (strcmp(args[1], "collision") == 0) {
        vga_set_color(VGA_RED, VGA_BLACK);
        vga_puts("[Bullet] AABB=12, Manifolds=3, Contacts=7, Impulse=12.4N\n");
        vga_set_color(VGA_WHITE, VGA_BLACK);
    } else if (strcmp(args[1], "raycast") == 0) {
        vga_set_color(VGA_LIGHT_CYAN, VGA_BLACK);
        vga_puts("[Bullet] Ray hit plane at t=0.998, dist=0.02m\n");
        vga_set_color(VGA_WHITE, VGA_BLACK);
    } else {
        vga_puts("Usage: bullet <init|rigidbody|softbody|constraint|collision|raycast>\n");
    }
}

static void cmd_vrep59(int argc, char args[][CMD_MAX_LEN]) {
    if (argc < 2) {
        vga_puts("Usage: coppeliasim <connect|scene|script|remote|joint|sensor>\n");
        return;
    }
    if (strcmp(args[1], "connect") == 0) {
        vga_set_color(VGA_LIGHT_GREEN, VGA_BLACK);
        vga_puts("[CoppeliaSim] Remote API on port 19997, client=123456\n");
        vga_set_color(VGA_WHITE, VGA_BLACK);
    } else if (strcmp(args[1], "scene") == 0) {
        vga_set_color(VGA_LIGHT_CYAN, VGA_BLACK);
        vga_puts("[CoppeliaSim] industrial_arms.ttt: 24 objs, 18 joints, 10 scripts\n");
        vga_set_color(VGA_WHITE, VGA_BLACK);
    } else if (strcmp(args[1], "script") == 0) {
        vga_set_color(VGA_LIGHT_GREEN, VGA_BLACK);
        vga_puts("[CoppeliaSim] controller.lua: RUN(line245), planner.py: IDLE\n");
        vga_set_color(VGA_WHITE, VGA_BLACK);
    } else if (strcmp(args[1], "remote") == 0) {
        vga_set_color(VGA_YELLOW, VGA_BLACK);
        vga_puts("[CoppeliaSim] API calls: 1247 (get_pos=342, set_tgt=298)\n");
        vga_set_color(VGA_WHITE, VGA_BLACK);
    } else if (strcmp(args[1], "joint") == 0) {
        vga_set_color(VGA_LIGHT_CYAN, VGA_BLACK);
        vga_puts("[CoppeliaSim] UR5: J1=12.5 J2=-45.2 J3=90 J4=0 J5=30.1 J6=-15.8\n");
        vga_set_color(VGA_WHITE, VGA_BLACK);
    } else if (strcmp(args[1], "sensor") == 0) {
        vga_set_color(VGA_LIGHT_GREEN, VGA_BLACK);
        vga_puts("[CoppeliaSim] prox=0.234m, vision=640x480(3obj), force=(0.12,0.03,-0.45)N\n");
        vga_set_color(VGA_WHITE, VGA_BLACK);
    } else {
        vga_puts("Usage: coppeliasim <connect|scene|script|remote|joint|sensor>\n");
    }
}
static void cmd_nengo59(int argc, char args[][CMD_MAX_LEN]) {
    if (argc < 2) {
        vga_puts("Usage: nengo <create|simulate|probe|transform|learn|network>\n");
        return;
    }
    if (strcmp(args[1], "create") == 0) {
        vga_set_color(VGA_LIGHT_GREEN, VGA_BLACK);
        vga_puts("[Nengo] Ensemble: 200 LIF neurons, 2D, radius=1.0\n");
        vga_set_color(VGA_WHITE, VGA_BLACK);
    } else if (strcmp(args[1], "simulate") == 0) {
        vga_set_color(VGA_LIGHT_CYAN, VGA_BLACK);
        vga_puts("[Nengo] NEF sim dt=1ms: out=[0.452,-0.128], RMS=0.023\n");
        vga_set_color(VGA_WHITE, VGA_BLACK);
    } else if (strcmp(args[1], "probe") == 0) {
        vga_set_color(VGA_YELLOW, VGA_BLACK);
        vga_puts("[Nengo] 3 probes: decoded(2D), spikes, voltage\n");
        vga_set_color(VGA_WHITE, VGA_BLACK);
    } else if (strcmp(args[1], "transform") == 0) {
        vga_set_color(VGA_LIGHT_CYAN, VGA_BLACK);
        vga_puts("[Nengo] Transform: in=2D, out=3D, matrix computed\n");
        vga_set_color(VGA_WHITE, VGA_BLACK);
    } else if (strcmp(args[1], "learn") == 0) {
        vga_set_color(VGA_LIGHT_GREEN, VGA_BLACK);
        vga_puts("[Nengo] PES rule: lr=0.001, epoch=5000, err_red=67.3%\n");
        vga_set_color(VGA_WHITE, VGA_BLACK);
    } else if (strcmp(args[1], "network") == 0) {
        vga_set_color(VGA_LIGHT_MAGENTA, VGA_BLACK);
        vga_puts("[Nengo] 5 ensembles, 7 connections, 850 neurons total\n");
        vga_set_color(VGA_WHITE, VGA_BLACK);
    } else {
        vga_puts("Usage: nengo <create|simulate|probe|transform|learn|network>\n");
    }
}

static void cmd_neuron59(int argc, char args[][CMD_MAX_LEN]) {
    if (argc < 2) {
        vga_puts("Usage: neuron <load|run|morphology|channel|synapse|currentclamp>\n");
        return;
    }
    if (strcmp(args[1], "load") == 0) {
        vga_set_color(VGA_LIGHT_GREEN, VGA_BLACK);
        vga_puts("[NEURON] cortical_pyramidal.hoc: 147 segs, 3 sections\n");
        vga_puts("[NEURON] Channels: Na, K, Ca, leak, h\n");
        vga_set_color(VGA_WHITE, VGA_BLACK);
    } else if (strcmp(args[1], "run") == 0) {
        vga_set_color(VGA_LIGHT_CYAN, VGA_BLACK);
        vga_puts("[NEURON] t=0-100ms, dt=25us: 12 spikes @ 120Hz\n");
        vga_puts("[NEURON] Vrest=-65mV, Vpeak=+35mV, Vth=-50mV\n");
        vga_set_color(VGA_WHITE, VGA_BLACK);
    } else if (strcmp(args[1], "morphology") == 0) {
        vga_set_color(VGA_YELLOW, VGA_BLACK);
        vga_puts("[NEURON] Soma: 20x15um | Apical: 350um(80seg) | Basal: 180um(66seg)\n");
        vga_set_color(VGA_WHITE, VGA_BLACK);
    } else if (strcmp(args[1], "channel") == 0) {
        vga_set_color(VGA_LIGHT_CYAN, VGA_BLACK);
        vga_puts("[NEURON] Na(open=0.34) K(open=0.72) Ca(open=0.12) @ t=50ms\n");
        vga_set_color(VGA_WHITE, VGA_BLACK);
    } else if (strcmp(args[1], "synapse") == 0) {
        vga_set_color(VGA_LIGHT_GREEN, VGA_BLACK);
        vga_puts("[NEURON] AMPA=12, NMDA=8, GABA_A=15 synapses\n");
        vga_set_color(VGA_WHITE, VGA_BLACK);
    } else if (strcmp(args[1], "currentclamp") == 0) {
        vga_set_color(VGA_YELLOW, VGA_BLACK);
        vga_puts("[NEURON] 0.5nA @ 100ms for 300ms: 34 spikes, 85Hz\n");
        vga_set_color(VGA_WHITE, VGA_BLACK);
    } else {
        vga_puts("Usage: neuron <load|run|morphology|channel|synapse|currentclamp>\n");
    }
}

static void cmd_brian259(int argc, char args[][CMD_MAX_LEN]) {
    if (argc < 2) {
        vga_puts("Usage: brian2 <equations|monitors|connections|spikes|rates|poisson>\n");
        return;
    }
    if (strcmp(args[1], "equations") == 0) {
        vga_set_color(VGA_LIGHT_GREEN, VGA_BLACK);
        vga_puts("[Brian2] dV/dt=(-V+I)/tau, tau=10ms, Vth=-50mV, Vreset=-70mV\n");
        vga_set_color(VGA_WHITE, VGA_BLACK);
    } else if (strcmp(args[1], "monitors") == 0) {
        vga_set_color(VGA_LIGHT_CYAN, VGA_BLACK);
        vga_puts("[Brian2] SpikeMon: 100 neurons, 847 spikes | StateMon: V,I,t\n");
        vga_set_color(VGA_WHITE, VGA_BLACK);
    } else if (strcmp(args[1], "connections") == 0) {
        vga_set_color(VGA_YELLOW, VGA_BLACK);
        vga_puts("[Brian2] Exe: 2340(5nS,0.5-2ms) | Inh: 1560(-10nS,0.5-3ms)\n");
        vga_set_color(VGA_WHITE, VGA_BLACK);
    } else if (strcmp(args[1], "spikes") == 0) {
        vga_set_color(VGA_LIGHT_MAGENTA, VGA_BLACK);
        vga_puts("[Brian2] Raster: burst1=12-18ms(45n), burst2=45-52ms(38n)\n");
        vga_set_color(VGA_WHITE, VGA_BLACK);
    } else if (strcmp(args[1], "rates") == 0) {
        vga_set_color(VGA_LIGHT_GREEN, VGA_BLACK);
        vga_puts("[Brian2] Rate: mean=42.3Hz, peak=189Hz, CV=0.37\n");
        vga_set_color(VGA_WHITE, VGA_BLACK);
    } else if (strcmp(args[1], "poisson") == 0) {
        vga_set_color(VGA_LIGHT_CYAN, VGA_BLACK);
        vga_puts("[Brian2] Poisson: 500n @ 100Hz, 4832 spikes in 100ms\n");
        vga_set_color(VGA_WHITE, VGA_BLACK);
    } else {
        vga_puts("Usage: brian2 <equations|monitors|connections|spikes|rates|poisson>\n");
    }
}

static void cmd_neo59(int argc, char args[][CMD_MAX_LEN]) {
    if (argc < 2) {
        vga_puts("Usage: neo-sim <load|analyze|filter|segment|spike|lfp>\n");
        return;
    }
    if (strcmp(args[1], "load") == 0) {
        vga_set_color(VGA_LIGHT_GREEN, VGA_BLACK);
        vga_puts("[Neo] NWB: 5 segs, 12 epochs, 64ch, 30kHz, 3600s\n");
        vga_set_color(VGA_WHITE, VGA_BLACK);
    } else if (strcmp(args[1], "analyze") == 0) {
        vga_set_color(VGA_LIGHT_CYAN, VGA_BLACK);
        vga_puts("[Neo] Seg1: 64ch analog, 48 units(sorted), 234 events\n");
        vga_set_color(VGA_WHITE, VGA_BLACK);
    } else if (strcmp(args[1], "filter") == 0) {
        vga_set_color(VGA_YELLOW, VGA_BLACK);
        vga_puts("[Neo] Butterworth order=4, 300-3000Hz, 64ch applied\n");
        vga_set_color(VGA_WHITE, VGA_BLACK);
    } else if (strcmp(args[1], "segment") == 0) {
        vga_set_color(VGA_LIGHT_GREEN, VGA_BLACK);
        vga_puts("[Neo] Seg0: 0-600s(50tr) Seg1: 600-1200s(48tr) Seg2: 1200-1800s(52tr)\n");
        vga_set_color(VGA_WHITE, VGA_BLACK);
    } else if (strcmp(args[1], "spike") == 0) {
        vga_set_color(VGA_LIGHT_CYAN, VGA_BLACK);
        vga_puts("[Neo] Unit1: 1234spk ISI=12.3ms CV=0.45 | Unit2: 892spk\n");
        vga_set_color(VGA_WHITE, VGA_BLACK);
    } else if (strcmp(args[1], "lfp") == 0) {
        vga_set_color(VGA_LIGHT_MAGENTA, VGA_BLACK);
        vga_puts("[Neo] LFP: Delta=45.2uV, Theta=32.1uV, Gamma=12.8uV\n");
        vga_set_color(VGA_WHITE, VGA_BLACK);
    } else {
        vga_puts("Usage: neo-sim <load|analyze|filter|segment|spike|lfp>\n");
    }
}
/* --- CFD & Multiphysics Simulation --- */

static void cmd_openfoam59(int argc, char args[][CMD_MAX_LEN]) {
    if (argc < 2) {
        vga_puts("Usage: openfoam <create|solve|mesh|boundary|turbulence|postprocess>\n");
        return;
    }
    if (strcmp(args[1], "create") == 0) {
        vga_set_color(VGA_LIGHT_GREEN, VGA_BLACK);
        vga_puts("[OpenFOAM] Case: lid_driven_cavity, Solver: icoFoam\n");
        vga_set_color(VGA_WHITE, VGA_BLACK);
    } else if (strcmp(args[1], "mesh") == 0) {
        vga_set_color(VGA_LIGHT_CYAN, VGA_BLACK);
        vga_puts("[OpenFOAM] blockMesh: 40x40x1=1600 hex, 5 patches\n");
        vga_set_color(VGA_WHITE, VGA_BLACK);
    } else if (strcmp(args[1], "solve") == 0) {
        vga_set_color(VGA_LIGHT_GREEN, VGA_BLACK);
        vga_puts("[OpenFOAM] icoFoam: dt=5ms, p-U res=1.2e-6, Umax=2.85m/s\n");
        vga_set_color(VGA_WHITE, VGA_BLACK);
    } else if (strcmp(args[1], "turbulence") == 0) {
        vga_set_color(VGA_YELLOW, VGA_BLACK);
        vga_puts("[OpenFOAM] kOmegaSST: k=0.15, omega=5.2, Re=1.5e6\n");
        vga_set_color(VGA_WHITE, VGA_BLACK);
    } else if (strcmp(args[1], "boundary") == 0) {
        vga_set_color(VGA_LIGHT_CYAN, VGA_BLACK);
        vga_puts("[OpenFOAM] inlet:U=(1,0,0) | outlet:noGrad | walls:no-slip\n");
        vga_set_color(VGA_WHITE, VGA_BLACK);
    } else if (strcmp(args[1], "postprocess") == 0) {
        vga_set_color(VGA_LIGHT_MAGENTA, VGA_BLACK);
        vga_puts("[OpenFOAM] Umax=2.85 pmax=12.4Pa Cd=1.23 Cl=0.04\n");
        vga_set_color(VGA_WHITE, VGA_BLACK);
    } else {
        vga_puts("Usage: openfoam <create|solve|mesh|boundary|turbulence|postprocess>\n");
    }
}

static void cmd_elmer59(int argc, char args[][CMD_MAX_LEN]) {
    if (argc < 2) {
        vga_puts("Usage: elmer <mesh|equations|solve|heat|stress|coupled>\n");
        return;
    }
    if (strcmp(args[1], "mesh") == 0) {
        vga_set_color(VGA_LIGHT_GREEN, VGA_BLACK);
        vga_puts("[Elmer] 12500 nodes, 48200 tets, quality=0.87\n");
        vga_set_color(VGA_WHITE, VGA_BLACK);
    } else if (strcmp(args[1], "equations") == 0) {
        vga_set_color(VGA_LIGHT_CYAN, VGA_BLACK);
        vga_puts("[Elmer] Heat(k=45) + Elasticity(E=210GPa,nu=0.3) + Electrostatics\n");
        vga_set_color(VGA_WHITE, VGA_BLACK);
    } else if (strcmp(args[1], "solve") == 0) {
        vga_set_color(VGA_LIGHT_GREEN, VGA_BLACK);
        vga_puts("[Elmer] BiCGStab+ILU2: 45 iters, res=2.3e-9, 8.4s\n");
        vga_set_color(VGA_WHITE, VGA_BLACK);
    } else if (strcmp(args[1], "heat") == 0) {
        vga_set_color(VGA_YELLOW, VGA_BLACK);
        vga_puts("[Elmer] Heat: Tmin=295.2K Tmax=342.8K grad=2340K/m\n");
        vga_set_color(VGA_WHITE, VGA_BLACK);
    } else if (strcmp(args[1], "stress") == 0) {
        vga_set_color(VGA_LIGHT_MAGENTA, VGA_BLACK);
        vga_puts("[Elmer] vonMises=145.2MPa, disp=0.12mm, SF=1.72\n");
        vga_set_color(VGA_WHITE, VGA_BLACK);
    } else if (strcmp(args[1], "coupled") == 0) {
        vga_set_color(VGA_LIGHT_CYAN, VGA_BLACK);
        vga_puts("[Elmer] Thermal-Structural: 5 iter, conv=YES, err=0.8%\n");
        vga_set_color(VGA_WHITE, VGA_BLACK);
    } else {
        vga_puts("Usage: elmer <mesh|equations|solve|heat|stress|coupled>\n");
    }
}

static void cmd_fenics59(int argc, char args[][CMD_MAX_LEN]) {
    if (argc < 2) {
        vga_puts("Usage: fenics <define|mesh|solve|variational|poisson|elasticity>\n");
        return;
    }
    if (strcmp(args[1], "define") == 0) {
        vga_set_color(VGA_LIGHT_GREEN, VGA_BLACK);
        vga_puts("[FEniCS] -div(grad(u))=f, u=0 on dOmega, P2 Lagrange\n");
        vga_set_color(VGA_WHITE, VGA_BLACK);
    } else if (strcmp(args[1], "mesh") == 0) {
        vga_set_color(VGA_LIGHT_CYAN, VGA_BLACK);
        vga_puts("[FEniCS] Unit square x4: 4225 verts, 4096 cells\n");
        vga_set_color(VGA_WHITE, VGA_BLACK);
    } else if (strcmp(args[1], "solve") == 0) {
        vga_set_color(VGA_LIGHT_GREEN, VGA_BLACK);
        vga_puts("[FEniCS] PETSc LU(mumps): 4225 DOFs, 38017 NNZ, 0.34s\n");
        vga_set_color(VGA_WHITE, VGA_BLACK);
    } else if (strcmp(args[1], "variational") == 0) {
        vga_set_color(VGA_YELLOW, VGA_BLACK);
        vga_puts("[FEniCS] a=inner(grad(u),grad(v))dx, L=f*vdx+g*vds\n");
        vga_set_color(VGA_WHITE, VGA_BLACK);
    } else if (strcmp(args[1], "poisson") == 0) {
        vga_set_color(VGA_LIGHT_CYAN, VGA_BLACK);
        vga_puts("[FEniCS] Poisson: L2=1.2e-6, H1=3.4e-4 (vs analytical)\n");
        vga_set_color(VGA_WHITE, VGA_BLACK);
    } else if (strcmp(args[1], "elasticity") == 0) {
        vga_set_color(VGA_LIGHT_MAGENTA, VGA_BLACK);
        vga_puts("[FEniCS] Elasticity: E=1, nu=0.3, disp_max=0.0142\n");
        vga_set_color(VGA_WHITE, VGA_BLACK);
    } else {
        vga_puts("Usage: fenics <define|mesh|solve|variational|poisson|elasticity>\n");
    }
}

static void cmd_dealii59(int argc, char args[][CMD_MAX_LEN]) {
    if (argc < 2) {
        vga_puts("Usage: dealii <triangulate|assemble|solve|refine|output|laplace>\n");
        return;
    }
    if (strcmp(args[1], "triangulate") == 0) {
        vga_set_color(VGA_LIGHT_GREEN, VGA_BLACK);
        vga_puts("[deal.II] 3D tri: 6144 cells, 5329 verts, 5 refinements\n");
        vga_set_color(VGA_WHITE, VGA_BLACK);
    } else if (strcmp(args[1], "assemble") == 0) {
        vga_set_color(VGA_LIGHT_CYAN, VGA_BLACK);
        vga_puts("[deal.II] DOFs=5329, NNZ=87234, assembly=2.1s\n");
        vga_set_color(VGA_WHITE, VGA_BLACK);
    } else if (strcmp(args[1], "solve") == 0) {
        vga_set_color(VGA_LIGHT_GREEN, VGA_BLACK);
        vga_puts("[deal.II] CG+AMG: 89 iters, res=1.4e-10, 0.56s\n");
        vga_set_color(VGA_WHITE, VGA_BLACK);
    } else if (strcmp(args[1], "refine") == 0) {
        vga_set_color(VGA_YELLOW, VGA_BLACK);
        vga_puts("[deal.II] Kelly estimator: 234 marked(25%), new=15876 cells\n");
        vga_set_color(VGA_WHITE, VGA_BLACK);
    } else if (strcmp(args[1], "output") == 0) {
        vga_set_color(VGA_LIGHT_CYAN, VGA_BLACK);
        vga_puts("[deal.II] VTK: 21317 points, 15876 cells, fields: u,grad_u\n");
        vga_set_color(VGA_WHITE, VGA_BLACK);
    } else if (strcmp(args[1], "laplace") == 0) {
        vga_set_color(VGA_LIGHT_MAGENTA, VGA_BLACK);
        vga_puts("[deal.II] L-shape: L2=8.7e-5, H1=2.3e-3, conv=O(h^1.33)\n");
        vga_set_color(VGA_WHITE, VGA_BLACK);
    } else {
        vga_puts("Usage: dealii <triangulate|assemble|solve|refine|output|laplace>\n");
    }
}
/* --- CAD/CAE Platforms --- */

static void cmd_salome59(int argc, char args[][CMD_MAX_LEN]) {
    if (argc < 2) {
        vga_puts("Usage: salome <geom|mesh|study|python|export|import>\n");
        return;
    }
    if (strcmp(args[1], "geom") == 0) {
        vga_set_color(VGA_LIGHT_GREEN, VGA_BLACK);
        vga_puts("[Salome] Geom: 6 shapes, 4 groups, Extrude/Fillet/Bool\n");
        vga_set_color(VGA_WHITE, VGA_BLACK);
    } else if (strcmp(args[1], "mesh") == 0) {
        vga_set_color(VGA_LIGHT_CYAN, VGA_BLACK);
        vga_puts("[Salome] Mesh: 45000 nodes, 128000 elems, min_angle=18.2deg\n");
        vga_set_color(VGA_WHITE, VGA_BLACK);
    } else if (strcmp(args[1], "study") == 0) {
        vga_set_color(VGA_YELLOW, VGA_BLACK);
        vga_puts("[Salome] Chain: Geom->Mesh->Calculix, 24 objs, 3 views\n");
        vga_set_color(VGA_WHITE, VGA_BLACK);
    } else if (strcmp(args[1], "python") == 0) {
        vga_set_color(VGA_LIGHT_GREEN, VGA_BLACK);
        vga_puts("[Salome] geompy.MakeBox(0,0,0,10,10,10) - 156 API fns\n");
        vga_set_color(VGA_WHITE, VGA_BLACK);
    } else if (strcmp(args[1], "export") == 0) {
        vga_set_color(VGA_LIGHT_CYAN, VGA_BLACK);
        vga_puts("[Salome] UNV export: 45000 nodes, 128000 elems, 2.3MB\n");
        vga_set_color(VGA_WHITE, VGA_BLACK);
    } else if (strcmp(args[1], "import") == 0) {
        vga_set_color(VGA_LIGHT_GREEN, VGA_BLACK);
        vga_puts("[Salome] STEP import: 8 solids, 64 faces, 192 edges\n");
        vga_set_color(VGA_WHITE, VGA_BLACK);
    } else {
        vga_puts("Usage: salome <geom|mesh|study|python|export|import>\n");
    }
}

static void cmd_freecad59(int argc, char args[][CMD_MAX_LEN]) {
    if (argc < 2) {
        vga_puts("Usage: freecad <new|part|assembly|parametric|export|render>\n");
        return;
    }
    if (strcmp(args[1], "new") == 0) {
        vga_set_color(VGA_LIGHT_GREEN, VGA_BLACK);
        vga_puts("[FreeCAD] New doc, Part Design workbench, MMKS units\n");
        vga_set_color(VGA_WHITE, VGA_BLACK);
    } else if (strcmp(args[1], "part") == 0) {
        vga_set_color(VGA_LIGHT_CYAN, VGA_BLACK);
        vga_puts("[FreeCAD] Bracket_v3: pad=20mm, 3x8mm holes, R3fillet\n");
        vga_set_color(VGA_WHITE, VGA_BLACK);
    } else if (strcmp(args[1], "assembly") == 0) {
        vga_set_color(VGA_YELLOW, VGA_BLACK);
        vga_puts("[FreeCAD] A2plus: 12 parts, 24 constraints, solve=OK\n");
        vga_set_color(VGA_WHITE, VGA_BLACK);
    } else if (strcmp(args[1], "parametric") == 0) {
        vga_set_color(VGA_LIGHT_CYAN, VGA_BLACK);
        vga_puts("[FreeCAD] w=50mm, h=80mm, t=3mm, hole=8mm, R=3mm\n");
        vga_set_color(VGA_WHITE, VGA_BLACK);
    } else if (strcmp(args[1], "export") == 0) {
        vga_set_color(VGA_LIGHT_GREEN, VGA_BLACK);
        vga_puts("[FreeCAD] STEP(245KB) STL(1.2MB,24800 tri) IGES(312KB)\n");
        vga_set_color(VGA_WHITE, VGA_BLACK);
    } else if (strcmp(args[1], "render") == 0) {
        vga_set_color(VGA_LIGHT_MAGENTA, VGA_BLACK);
        vga_puts("[FreeCAD] LuxRender 1920x1080, 3 materials, 12.4s\n");
        vga_set_color(VGA_WHITE, VGA_BLACK);
    } else {
        vga_puts("Usage: freecad <new|part|assembly|parametric|export|render>\n");
    }
}

static void cmd_opencascade59(int argc, char args[][CMD_MAX_LEN]) {
    if (argc < 2) {
        vga_puts("Usage: occt <brep|boolean|fillet|surface|nurbs|tessellate>\n");
        return;
    }
    if (strcmp(args[1], "brep") == 0) {
        vga_set_color(VGA_LIGHT_GREEN, VGA_BLACK);
        vga_puts("[OCCT] BRep: 2 solids, 4 shells, 32 faces, 128 edges\n");
        vga_set_color(VGA_WHITE, VGA_BLACK);
    } else if (strcmp(args[1], "boolean") == 0) {
        vga_set_color(VGA_LIGHT_CYAN, VGA_BLACK);
        vga_puts("[OCCT] Union(24f) + Cut(18f) + Common(6f) = OK\n");
        vga_set_color(VGA_WHITE, VGA_BLACK);
    } else if (strcmp(args[1], "fillet") == 0) {
        vga_set_color(VGA_YELLOW, VGA_BLACK);
        vga_puts("[OCCT] Fillet R=2.5mm(12 edges) + Chamfer 1mm(8 edges)\n");
        vga_set_color(VGA_WHITE, VGA_BLACK);
    } else if (strcmp(args[1], "surface") == 0) {
        vga_set_color(VGA_LIGHT_CYAN, VGA_BLACK);
        vga_puts("[OCCT] B-Spline surf: U3xV4, 20x16 pts, G1=94.2%\n");
        vga_set_color(VGA_WHITE, VGA_BLACK);
    } else if (strcmp(args[1], "nurbs") == 0) {
        vga_set_color(VGA_LIGHT_GREEN, VGA_BLACK);
        vga_puts("[OCCT] NURBS: deg=3, knots=8, poles=10, bounds=100x50x25\n");
        vga_set_color(VGA_WHITE, VGA_BLACK);
    } else if (strcmp(args[1], "tessellate") == 0) {
        vga_set_color(VGA_LIGHT_MAGENTA, VGA_BLACK);
        vga_puts("[OCCT] Tess: 48200 tri, 25100 verts, 0.1mm deflection\n");
        vga_set_color(VGA_WHITE, VGA_BLACK);
    } else {
        vga_puts("Usage: occt <brep|boolean|fillet|surface|nurbs|tessellate>\n");
    }
}

static void cmd_openscad59(int argc, char args[][CMD_MAX_LEN]) {
    if (argc < 2) {
        vga_puts("Usage: openscad <compile|preview|render|module|difference|union>\n");
        return;
    }
    if (strcmp(args[1], "compile") == 0) {
        vga_set_color(VGA_LIGHT_GREEN, VGA_BLACK);
        vga_puts("[OpenSCAD] bracket.scad: 14 modules, 32 primitives, 0 warnings\n");
        vga_set_color(VGA_WHITE, VGA_BLACK);
    } else if (strcmp(args[1], "preview") == 0) {
        vga_set_color(VGA_LIGHT_CYAN, VGA_BLACK);
        vga_puts("[OpenSCAD] F5 preview: 24800 poly, 50x80x20mm, 0.23s\n");
        vga_set_color(VGA_WHITE, VGA_BLACK);
    } else if (strcmp(args[1], "render") == 0) {
        vga_set_color(VGA_LIGHT_GREEN, VGA_BLACK);
        vga_puts("[OpenSCAD] F6 render: 6 unions+3 diffs, 48200 tri, 3.2s\n");
        vga_set_color(VGA_WHITE, VGA_BLACK);
    } else if (strcmp(args[1], "module") == 0) {
        vga_set_color(VGA_YELLOW, VGA_BLACK);
        vga_puts("[OpenSCAD] bracket()->base_plate()+arms()+holes(), w=50,d=30,h=20\n");
        vga_set_color(VGA_WHITE, VGA_BLACK);
    } else if (strcmp(args[1], "difference") == 0) {
        vga_set_color(VGA_LIGHT_CYAN, VGA_BLACK);
        vga_puts("[OpenSCAD] cube(50,80,20) - 4xcyl(r=4,h=25) = 4 holes\n");
        vga_set_color(VGA_WHITE, VGA_BLACK);
    } else if (strcmp(args[1], "union") == 0) {
        vga_set_color(VGA_LIGHT_GREEN, VGA_BLACK);
        vga_puts("[OpenSCAD] cube+2cyls+sphere: 42 faces, 0 self-int\n");
        vga_set_color(VGA_WHITE, VGA_BLACK);
    } else {
        vga_puts("Usage: openscad <compile|preview|render|module|difference|union>\n");
    }
}

static void cmd_solvespace59(int argc, char args[][CMD_MAX_LEN]) {
    if (argc < 2) {
        vga_puts("Usage: solvespace <sketch|extrude|revolve|constraint|solve|export>\n");
        return;
    }
    if (strcmp(args[1], "sketch") == 0) {
        vga_set_color(VGA_LIGHT_GREEN, VGA_BLACK);
        vga_puts("[SolveSpace] XY sketch: 12 lines, 4 arcs, 6 circles, 22 constraints\n");
        vga_set_color(VGA_WHITE, VGA_BLACK);
    } else if (strcmp(args[1], "extrude") == 0) {
        vga_set_color(VGA_LIGHT_CYAN, VGA_BLACK);
        vga_puts("[SolveSpace] Extrude +Z 20mm: 14 faces, 30 edges\n");
        vga_set_color(VGA_WHITE, VGA_BLACK);
    } else if (strcmp(args[1], "revolve") == 0) {
        vga_set_color(VGA_YELLOW, VGA_BLACK);
        vga_puts("[SolveSpace] Revolve X-axis 360deg: 8 faces\n");
        vga_set_color(VGA_WHITE, VGA_BLACK);
    } else if (strcmp(args[1], "constraint") == 0) {
        vga_set_color(VGA_LIGHT_CYAN, VGA_BLACK);
        vga_puts("[SolveSpace] DOF=0 (fully constrained), Jacobian=1.0\n");
        vga_set_color(VGA_WHITE, VGA_BLACK);
    } else if (strcmp(args[1], "solve") == 0) {
        vga_set_color(VGA_LIGHT_GREEN, VGA_BLACK);
        vga_puts("[SolveSpace] Newton: 4 iters, RMS=1.2e-12, all satisfied\n");
        vga_set_color(VGA_WHITE, VGA_BLACK);
    } else if (strcmp(args[1], "export") == 0) {
        vga_set_color(VGA_LIGHT_MAGENTA, VGA_BLACK);
        vga_puts("[SolveSpace] STEP(89KB) STL(320KB) SVG(12KB)\n");
        vga_set_color(VGA_WHITE, VGA_BLACK);
    } else {
        vga_puts("Usage: solvespace <sketch|extrude|revolve|constraint|solve|export>\n");
    }
}

static void cmd_librecad59(int argc, char args[][CMD_MAX_LEN]) {
    if (argc < 2) {
        vga_puts("Usage: librecad <draw|dimension|layer|block|hatch|export>\n");
        return;
    }
    if (strcmp(args[1], "draw") == 0) {
        vga_set_color(VGA_LIGHT_GREEN, VGA_BLACK);
        vga_puts("[LibreCAD] 91 entities: 45 lines, 12 arcs, 8 circles, 14 dims\n");
        vga_set_color(VGA_WHITE, VGA_BLACK);
    } else if (strcmp(args[1], "dimension") == 0) {
        vga_set_color(VGA_LIGHT_CYAN, VGA_BLACK);
        vga_puts("[LibreCAD] Linear=8, Aligned=3, Angular=2, Radius=1, tol=0.1mm\n");
        vga_set_color(VGA_WHITE, VGA_BLACK);
    } else if (strcmp(args[1], "layer") == 0) {
        vga_set_color(VGA_YELLOW, VGA_BLACK);
        vga_puts("[LibreCAD] 4 layers: default(34), CONSTR(12), DIM(14), HIDDEN(8)\n");
        vga_set_color(VGA_WHITE, VGA_BLACK);
    } else if (strcmp(args[1], "block") == 0) {
        vga_set_color(VGA_LIGHT_CYAN, VGA_BLACK);
        vga_puts("[LibreCAD] SCREW_M6: 12 ent,16 ins | WASHER: 6 ent,8 ins\n");
        vga_set_color(VGA_WHITE, VGA_BLACK);
    } else if (strcmp(args[1], "hatch") == 0) {
        vga_set_color(VGA_LIGHT_GREEN, VGA_BLACK);
        vga_puts("[LibreCAD] ANSI31(3 regions,45deg) + SOLID(2 regions)\n");
        vga_set_color(VGA_WHITE, VGA_BLACK);
    } else if (strcmp(args[1], "export") == 0) {
        vga_set_color(VGA_LIGHT_MAGENTA, VGA_BLACK);
        vga_puts("[LibreCAD] DXF(45KB) PDF(128KB,A3) SVG(67KB)\n");
        vga_set_color(VGA_WHITE, VGA_BLACK);
    } else {
        vga_puts("Usage: librecad <draw|dimension|layer|block|hatch|export>\n");
    }
}
/* --- Electronics Design --- */

static void cmd_kicad59(int argc, char args[][CMD_MAX_LEN]) {
    if (argc < 2) {
        vga_puts("Usage: kicad <schematic|pcb|drc|erc|rercoute|bom>\n");
        return;
    }
    if (strcmp(args[1], "schematic") == 0) {
        vga_set_color(VGA_LIGHT_GREEN, VGA_BLACK);
        vga_puts("[KiCad] power_supply_v2: 34 syms, 87 wires, 2 hier-sheets\n");
        vga_set_color(VGA_WHITE, VGA_BLACK);
    } else if (strcmp(args[1], "pcb") == 0) {
        vga_set_color(VGA_LIGHT_CYAN, VGA_BLACK);
        vga_puts("[KiCad] PCB: 34 footprints, 245 tracks, 3 zones, 85x52mm\n");
        vga_set_color(VGA_WHITE, VGA_BLACK);
    } else if (strcmp(args[1], "drc") == 0) {
        vga_set_color(VGA_YELLOW, VGA_BLACK);
        vga_puts("[KiCad] DRC: clear=0.15mm, trace=0.25mm, err=0, warn=2\n");
        vga_set_color(VGA_WHITE, VGA_BLACK);
    } else if (strcmp(args[1], "erc") == 0) {
        vga_set_color(VGA_LIGHT_CYAN, VGA_BLACK);
        vga_puts("[KiCad] ERC: unconn=0, multi_drv=0, pwr_flag=1 warn\n");
        vga_set_color(VGA_WHITE, VGA_BLACK);
    } else if (strcmp(args[1], "rercoute") == 0) {
        vga_set_color(VGA_LIGHT_GREEN, VGA_BLACK);
        vga_puts("[KiCad] Routed: 245/245(100%), vias=28, len=4523mm\n");
        vga_set_color(VGA_WHITE, VGA_BLACK);
    } else if (strcmp(args[1], "bom") == 0) {
        vga_set_color(VGA_LIGHT_MAGENTA, VGA_BLACK);
        vga_puts("[KiCad] BOM: R=18, C=12, L=2, IC=1, D=1, Conn=2 => 48 parts\n");
        vga_set_color(VGA_WHITE, VGA_BLACK);
    } else {
        vga_puts("Usage: kicad <schematic|pcb|drc|erc|rercoute|bom>\n");
    }
}

static void cmd_gerber59(int argc, char args[][CMD_MAX_LEN]) {
    if (argc < 2) {
        vga_puts("Usage: gerber <generate|verify|drill|outline|silk|fabricate>\n");
        return;
    }
    if (strcmp(args[1], "generate") == 0) {
        vga_set_color(VGA_LIGHT_GREEN, VGA_BLACK);
        vga_puts("[Gerber] 8 files: F.Cu(245KB) B.Cu(198KB) Silk(45KB) Mask(67KB)\n");
        vga_set_color(VGA_WHITE, VGA_BLACK);
    } else if (strcmp(args[1], "verify") == 0) {
        vga_set_color(VGA_LIGHT_CYAN, VGA_BLACK);
        vga_puts("[Gerber] RS-274X, mm, 42 apertures, err=0, warn=0\n");
        vga_set_color(VGA_WHITE, VGA_BLACK);
    } else if (strcmp(args[1], "drill") == 0) {
        vga_set_color(VGA_YELLOW, VGA_BLACK);
        vga_puts("[Gerber] Excellon: 124 holes (98 plated, 26 NPTH)\n");
        vga_set_color(VGA_WHITE, VGA_BLACK);
    } else if (strcmp(args[1], "outline") == 0) {
        vga_set_color(VGA_LIGHT_CYAN, VGA_BLACK);
        vga_puts("[Gerber] Edge.Cuts: 85x52mm, R2mm fillets\n");
        vga_set_color(VGA_WHITE, VGA_BLACK);
    } else if (strcmp(args[1], "silk") == 0) {
        vga_set_color(VGA_LIGHT_GREEN, VGA_BLACK);
        vga_puts("[Gerber] Front: 34 refs+12 vals+logo | Back: 6 refs\n");
        vga_set_color(VGA_WHITE, VGA_BLACK);
    } else if (strcmp(args[1], "fabricate") == 0) {
        vga_set_color(VGA_LIGHT_MAGENTA, VGA_BLACK);
        vga_puts("[Gerber] Fab pkg: 10 files, 892KB, 2-layer, HASL, 1oz Cu\n");
        vga_set_color(VGA_WHITE, VGA_BLACK);
    } else {
        vga_puts("Usage: gerber <generate|verify|drill|outline|silk|fabricate>\n");
    }
}

/* --- EM & Circuit Simulation --- */

static void cmd_openems59(int argc, char args[][CMD_MAX_LEN]) {
    if (argc < 2) {
        vga_puts("Usage: openEMS <mesh|excite|simulate|sparameter|field|near2far>\n");
        return;
    }
    if (strcmp(args[1], "mesh") == 0) {
        vga_set_color(VGA_LIGHT_GREEN, VGA_BLACK);
        vga_puts("[openEMS] FDTD: 200x150x100 cells, dx=0.1mm, PML=8\n");
        vga_set_color(VGA_WHITE, VGA_BLACK);
    } else if (strcmp(args[1], "excite") == 0) {
        vga_set_color(VGA_LIGHT_CYAN, VGA_BLACK);
        vga_puts("[openEMS] Gaussian: Fc=10GHz, port=50ohm, Z0=377ohm\n");
        vga_set_color(VGA_WHITE, VGA_BLACK);
    } else if (strcmp(args[1], "simulate") == 0) {
        vga_set_color(VGA_LIGHT_GREEN, VGA_BLACK);
        vga_puts("[openEMS] 20000 steps, -60dB@step18500, 9.5s wall\n");
        vga_set_color(VGA_WHITE, VGA_BLACK);
    } else if (strcmp(args[1], "sparameter") == 0) {
        vga_set_color(VGA_YELLOW, VGA_BLACK);
        vga_puts("[openEMS] S11=-18.2dB S21=-0.3dB @10GHz (2-port)\n");
        vga_set_color(VGA_WHITE, VGA_BLACK);
    } else if (strcmp(args[1], "field") == 0) {
        vga_set_color(VGA_LIGHT_CYAN, VGA_BLACK);
        vga_puts("[openEMS] Ey=12.4V/m, Hz=0.033A/m, SAR=0.45W/kg\n");
        vga_set_color(VGA_WHITE, VGA_BLACK);
    } else if (strcmp(args[1], "near2far") == 0) {
        vga_set_color(VGA_LIGHT_MAGENTA, VGA_BLACK);
        vga_puts("[openEMS] NF2FF: 12.4dBi, BW3dB=62deg, FBR=18.2dB\n");
        vga_set_color(VGA_WHITE, VGA_BLACK);
    } else {
        vga_puts("Usage: openEMS <mesh|excite|simulate|sparameter|field|near2far>\n");
    }
}

static void cmd_qucs59(int argc, char args[][CMD_MAX_LEN]) {
    if (argc < 2) {
        vga_puts("Usage: qucs <schematic|simulate|dc|ac|transient|parametric>\n");
        return;
    }
    if (strcmp(args[1], "schematic") == 0) {
        vga_set_color(VGA_LIGHT_GREEN, VGA_BLACK);
        vga_puts("[Qucs] lowpass_filter: R=3,L=2,C=2,Src=1,14 wires\n");
        vga_set_color(VGA_WHITE, VGA_BLACK);
    } else if (strcmp(args[1], "simulate") == 0) {
        vga_set_color(VGA_LIGHT_CYAN, VGA_BLACK);
        vga_puts("[Qucs] Qucsator: 200 pts, 1Hz-100MHz sweep\n");
        vga_set_color(VGA_WHITE, VGA_BLACK);
    } else if (strcmp(args[1], "dc") == 0) {
        vga_set_color(VGA_YELLOW, VGA_BLACK);
        vga_puts("[Qucs] DC: V(R1)=2.34V I=2.34mA Vout=1.25V\n");
        vga_set_color(VGA_WHITE, VGA_BLACK);
    } else if (strcmp(args[1], "ac") == 0) {
        vga_set_color(VGA_LIGHT_CYAN, VGA_BLACK);
        vga_puts("[Qucs] AC: fc=15.9kHz, pass=0dB, stop=-45dB@1MHz, -40dB/dec\n");
        vga_set_color(VGA_WHITE, VGA_BLACK);
    } else if (strcmp(args[1], "transient") == 0) {
        vga_set_color(VGA_LIGHT_GREEN, VGA_BLACK);
        vga_puts("[Qucs] Tran: 1ms,1us step, square 1kHz, OS=2.1%, tr=22us\n");
        vga_set_color(VGA_WHITE, VGA_BLACK);
    } else if (strcmp(args[1], "parametric") == 0) {
        vga_set_color(VGA_LIGHT_MAGENTA, VGA_BLACK);
        vga_puts("[Qucs] Sweep C1: 1nF-100nF, fc: 1.6kHz-159kHz\n");
        vga_set_color(VGA_WHITE, VGA_BLACK);
    } else {
        vga_puts("Usage: qucs <schematic|simulate|dc|ac|transient|parametric>\n");
    }
}

static void cmd_ngspice59(int argc, char args[][CMD_MAX_LEN]) {
    if (argc < 2) {
        vga_puts("Usage: ngspice <source|dc|ac|transient|noise|montecarlo>\n");
        return;
    }
    if (strcmp(args[1], "source") == 0) {
        vga_set_color(VGA_LIGHT_GREEN, VGA_BLACK);
        vga_puts("[ngspice] diff_amp.spice: 5 MOS, 8 R, BSIM3v3, Vdd=3.3V\n");
        vga_set_color(VGA_WHITE, VGA_BLACK);
    } else if (strcmp(args[1], "dc") == 0) {
        vga_set_color(VGA_LIGHT_CYAN, VGA_BLACK);
        vga_puts("[ngspice] DC: Vin=0->3.3V, Vout(0)=3.3V, Vout(1.65)=1.68V\n");
        vga_set_color(VGA_WHITE, VGA_BLACK);
    } else if (strcmp(args[1], "ac") == 0) {
        vga_set_color(VGA_YELLOW, VGA_BLACK);
        vga_puts("[ngspice] AC: gain=42.3dB, f-3dB=8.7MHz, GBW=180MHz, PM=65deg\n");
        vga_set_color(VGA_WHITE, VGA_BLACK);
    } else if (strcmp(args[1], "transient") == 0) {
        vga_set_color(VGA_LIGHT_GREEN, VGA_BLACK);
        vga_puts("[ngspice] Tran: 10us, 10MHz sine 100mVpp -> 4.23Vpp, THD=0.12%\n");
        vga_set_color(VGA_WHITE, VGA_BLACK);
    } else if (strcmp(args[1], "noise") == 0) {
        vga_set_color(VGA_LIGHT_CYAN, VGA_BLACK);
        vga_puts("[ngspice] Noise: in=3.2nV/rHz, out=135nV/rHz@1kHz, NF=1.8dB\n");
        vga_set_color(VGA_WHITE, VGA_BLACK);
    } else if (strcmp(args[1], "montecarlo") == 0) {
        vga_set_color(VGA_LIGHT_MAGENTA, VGA_BLACK);
        vga_puts("[ngspice] MC(1000): Vout=1.68V+-0.042V, yield=97.3%\n");
        vga_set_color(VGA_WHITE, VGA_BLACK);
    } else {
        vga_puts("Usage: ngspice <source|dc|ac|transient|noise|montecarlo>\n");
    }
}
static void cmd_xyce59(int argc, char args[][CMD_MAX_LEN]) {
    if (argc < 2) {
        vga_puts("Usage: xyce <netlist|dc|ac|tran|sensitivity|hb>\n");
        return;
    }
    if (strcmp(args[1], "netlist") == 0) {
        vga_set_color(VGA_LIGHT_GREEN, VGA_BLACK);
        vga_puts("[Xyce] rf_amplifier.cir: 12 dev, BFP740F SiGe HBT\n");
        vga_set_color(VGA_WHITE, VGA_BLACK);
    } else if (strcmp(args[1], "dc") == 0) {
        vga_set_color(VGA_LIGHT_CYAN, VGA_BLACK);
        vga_puts("[Xyce] DC: Vcc=1.0-3.6V, ICc(1.8V)=5.2mA, ICc(3.0V)=8.7mA\n");
        vga_set_color(VGA_WHITE, VGA_BLACK);
    } else if (strcmp(args[1], "ac") == 0) {
        vga_set_color(VGA_YELLOW, VGA_BLACK);
        vga_puts("[Xyce] AC 1MHz-40GHz: S21=18.5dB S11=-15.2dB NF=1.2dB\n");
        vga_set_color(VGA_WHITE, VGA_BLACK);
    } else if (strcmp(args[1], "tran") == 0) {
        vga_set_color(VGA_LIGHT_GREEN, VGA_BLACK);
        vga_puts("[Xyce] Tran: 100ns, max_dt=0.1ns, Gear2, 1000 steps\n");
        vga_set_color(VGA_WHITE, VGA_BLACK);
    } else if (strcmp(args[1], "sensitivity") == 0) {
        vga_set_color(VGA_LIGHT_CYAN, VGA_BLACK);
        vga_puts("[Xyce] dG/dR1=-0.042dB/ohm, dBW/dC1=-12.3MHz/pF\n");
        vga_set_color(VGA_WHITE, VGA_BLACK);
    } else if (strcmp(args[1], "hb") == 0) {
        vga_set_color(VGA_LIGHT_MAGENTA, VGA_BLACK);
        vga_puts("[Xyce] HB: 2.4GHz x5 harm, Pout=10.2dBm, HD2=-32.1dBc\n");
        vga_set_color(VGA_WHITE, VGA_BLACK);
    } else {
        vga_puts("Usage: xyce <netlist|dc|ac|tran|sensitivity|hb>\n");
    }
}

static void cmd_lumerical59(int argc, char args[][CMD_MAX_LEN]) {
    if (argc < 2) {
        vga_puts("Usage: lumerical <fdtd|mode|parameterize|export|convergence|ring>\n");
        return;
    }
    if (strcmp(args[1], "fdtd") == 0) {
        vga_set_color(VGA_LIGHT_GREEN, VGA_BLACK);
        vga_puts("[Lumerical] FDTD: 500x500x200, dx=25nm, TFSF 1500-1600nm\n");
        vga_set_color(VGA_WHITE, VGA_BLACK);
    } else if (strcmp(args[1], "mode") == 0) {
        vga_set_color(VGA_LIGHT_CYAN, VGA_BLACK);
        vga_puts("[Lumerical] MODE: Si 500x220nm, 4 modes, TE0 neff=2.456\n");
        vga_set_color(VGA_WHITE, VGA_BLACK);
    } else if (strcmp(args[1], "parameterize") == 0) {
        vga_set_color(VGA_YELLOW, VGA_BLACK);
        vga_puts("[Lumerical] Sweep width 400-700nm: neff=2.312-2.589\n");
        vga_set_color(VGA_WHITE, VGA_BLACK);
    } else if (strcmp(args[1], "export") == 0) {
        vga_set_color(VGA_LIGHT_GREEN, VGA_BLACK);
        vga_puts("[Lumerical] E_field.ldf(45MB) S_params.ldf(12KB) modes.ldf(8KB)\n");
        vga_set_color(VGA_WHITE, VGA_BLACK);
    } else if (strcmp(args[1], "convergence") == 0) {
        vga_set_color(VGA_LIGHT_CYAN, VGA_BLACK);
        vga_puts("[Lumerical] Mesh=3, power balance: src=1 abs=0.85 trans=0.12, err=3%\n");
        vga_set_color(VGA_WHITE, VGA_BLACK);
    } else if (strcmp(args[1], "ring") == 0) {
        vga_set_color(VGA_LIGHT_MAGENTA, VGA_BLACK);
        vga_puts("[Lumerical] Ring: R=10um gap=200nm FSR=2.6nm Q=12000\n");
        vga_set_color(VGA_WHITE, VGA_BLACK);
    } else {
        vga_puts("Usage: lumerical <fdtd|mode|parameterize|export|convergence|ring>\n");
    }
}

static void cmd_mEEP59(int argc, char args[][CMD_MAX_LEN]) {
    if (argc < 2) {
        vga_puts("Usage: meep <cell|sources|materials|fields|sparameter|farfield>\n");
        return;
    }
    if (strcmp(args[1], "cell") == 0) {
        vga_set_color(VGA_LIGHT_GREEN, VGA_BLACK);
        vga_puts("[Meep] 3D cell: 20x20x10um, res=50px/um, PML=1um\n");
        vga_set_color(VGA_WHITE, VGA_BLACK);
    } else if (strcmp(args[1], "sources") == 0) {
        vga_set_color(VGA_LIGHT_CYAN, VGA_BLACK);
        vga_puts("[Meep] GaussianSource fc=1.0(1550nm) Ez @ (5,10,5)um\n");
        vga_set_color(VGA_WHITE, VGA_BLACK);
    } else if (strcmp(args[1], "materials") == 0) {
        vga_set_color(VGA_YELLOW, VGA_BLACK);
        vga_puts("[Meep] Si:eps=12.25 | SiO2:eps=2.1 | Air:eps=1.0\n");
        vga_set_color(VGA_WHITE, VGA_BLACK);
    } else if (strcmp(args[1], "fields") == 0) {
        vga_set_color(VGA_LIGHT_CYAN, VGA_BLACK);
        vga_puts("[Meep] Hz=0.92, Ex=0.45, Ey=0.38, energy=2.34e-14 J/um3\n");
        vga_set_color(VGA_WHITE, VGA_BLACK);
    } else if (strcmp(args[1], "sparameter") == 0) {
        vga_set_color(VGA_LIGHT_GREEN, VGA_BLACK);
        vga_puts("[Meep] S11=-22.4dB S21=-0.8dB @1550nm, 200 pts 1500-1600nm\n");
        vga_set_color(VGA_WHITE, VGA_BLACK);
    } else if (strcmp(args[1], "farfield") == 0) {
        vga_set_color(VGA_LIGHT_MAGENTA, VGA_BLACK);
        vga_puts("[Meep] NF2FF: 1000um, dir=15.2dBi, BW3dB=8.5deg\n");
        vga_set_color(VGA_WHITE, VGA_BLACK);
    } else {
        vga_puts("Usage: meep <cell|sources|materials|fields|sparameter|farfield>\n");
    }
}
/* --- Commercial-Grade Simulation --- */

static void cmd_ansys59(int argc, char args[][CMD_MAX_LEN]) {
    if (argc < 2) {
        vga_puts("Usage: ansys <mechanical|fluent|hfss|maxwell|lsdyna|workbench>\n");
        return;
    }
    if (strcmp(args[1], "mechanical") == 0) {
        vga_set_color(VGA_LIGHT_GREEN, VGA_BLACK);
        vga_puts("[Ansys Mechanical] 285K nodes, 142K hex, Steel 304, E=193GPa\n");
        vga_set_color(VGA_WHITE, VGA_BLACK);
        vga_puts("[Ansys Mechanical] disp_max=0.082mm, stress_max=156MPa\n");
    } else if (strcmp(args[1], "fluent") == 0) {
        vga_set_color(VGA_LIGHT_CYAN, VGA_BLACK);
        vga_puts("[Ansys Fluent] 2.4M poly cells, k-omega SST, y+<1\n");
        vga_set_color(VGA_WHITE, VGA_BLACK);
        vga_puts("[Ansys Fluent] Conv 845 iters: Cd=0.342 Cl=0.018\n");
    } else if (strcmp(args[1], "hfss") == 0) {
        vga_set_color(VGA_YELLOW, VGA_BLACK);
        vga_puts("[Ansys HFSS] FEM tet adaptive, patch 2.4GHz\n");
        vga_set_color(VGA_WHITE, VGA_BLACK);
        vga_puts("[Ansys HFSS] S11=-28.5dB Gain=8.2dBi BW=85MHz\n");
    } else if (strcmp(args[1], "maxwell") == 0) {
        vga_set_color(VGA_LIGHT_CYAN, VGA_BLACK);
        vga_puts("[Ansys Maxwell] 2D Transient IPMSM 4-pair 3000RPM\n");
        vga_set_color(VGA_WHITE, VGA_BLACK);
        vga_puts("[Ansys Maxwell] Torque=12.5Nm Flux=0.038Wb\n");
    } else if (strcmp(args[1], "lsdyna") == 0) {
        vga_set_color(VGA_LIGHT_GREEN, VGA_BLACK);
        vga_puts("[Ansys LS-DYNA] car crash 56km/h: 42 parts 1.2M nodes\n");
        vga_set_color(VGA_WHITE, VGA_BLACK);
        vga_puts("[Ansys LS-DYNA] 100ms, max_def=185mm, energy OK\n");
    } else if (strcmp(args[1], "workbench") == 0) {
        vga_set_color(VGA_LIGHT_MAGENTA, VGA_BLACK);
        vga_puts("[Ansys Workbench] 4 systems, 3/4 solved, geometry shared\n");
        vga_set_color(VGA_WHITE, VGA_BLACK);
    } else {
        vga_puts("Usage: ansys <mechanical|fluent|hfss|maxwell|lsdyna|workbench>\n");
    }
}

static void cmd_comsol59(int argc, char args[][CMD_MAX_LEN]) {
    if (argc < 2) {
        vga_puts("Usage: comsol <geometry|mesh|physics|study|results|coupling>\n");
        return;
    }
    if (strcmp(args[1], "geometry") == 0) {
        vga_set_color(VGA_LIGHT_GREEN, VGA_BLACK);
        vga_puts("[COMSOL] cylinder(r=25,h=50)+box(10), union, R2 fillet, V=98.2cm3\n");
        vga_set_color(VGA_WHITE, VGA_BLACK);
    } else if (strcmp(args[1], "mesh") == 0) {
        vga_set_color(VGA_LIGHT_CYAN, VGA_BLACK);
        vga_puts("[COMSOL] Free tet: 85K nodes, 312K elems, 5 BL layers\n");
        vga_set_color(VGA_WHITE, VGA_BLACK);
    } else if (strcmp(args[1], "physics") == 0) {
        vga_set_color(VGA_YELLOW, VGA_BLACK);
        vga_puts("[COMSOL] ht(solid) + solid(structural) + coupled\n");
        vga_set_color(VGA_WHITE, VGA_BLACK);
    } else if (strcmp(args[1], "study") == 0) {
        vga_set_color(VGA_LIGHT_GREEN, VGA_BLACK);
        vga_puts("[COMSOL] Stationary Newton-Raphson: 6 iter, conv=YES, 255K DOFs\n");
        vga_set_color(VGA_WHITE, VGA_BLACK);
    } else if (strcmp(args[1], "results") == 0) {
        vga_set_color(VGA_LIGHT_CYAN, VGA_BLACK);
        vga_puts("[COMSOL] T=452K max, vonMises=89.2MPa, disp=0.045mm\n");
        vga_set_color(VGA_WHITE, VGA_BLACK);
    } else if (strcmp(args[1], "coupling") == 0) {
        vga_set_color(VGA_LIGHT_MAGENTA, VGA_BLACK);
        vga_puts("[COMSOL] Thermo-structural bidir: 3 iter, res=2.1e-9\n");
        vga_set_color(VGA_WHITE, VGA_BLACK);
    } else {
        vga_puts("Usage: comsol <geometry|mesh|physics|study|results|coupling>\n");
    }
}
/* --- Scientific Computing --- */

static void cmd_matlab59(int argc, char args[][CMD_MAX_LEN]) {
    if (argc < 2) {
        vga_puts("Usage: matlab <workspace|matrix|plot|ode|fft|eigenvalue>\n");
        return;
    }
    if (strcmp(args[1], "workspace") == 0) {
        vga_set_color(VGA_LIGHT_GREEN, VGA_BLACK);
        vga_puts("[MATLAB] 24 vars, 1.2MB, largest A(1000x1000 double)\n");
        vga_set_color(VGA_WHITE, VGA_BLACK);
    } else if (strcmp(args[1], "matrix") == 0) {
        vga_set_color(VGA_LIGHT_CYAN, VGA_BLACK);
        vga_puts("[MATLAB] A(100)x B(100x50): 2.3ms | det=1.42e12 rank=98\n");
        vga_set_color(VGA_WHITE, VGA_BLACK);
    } else if (strcmp(args[1], "ode") == 0) {
        vga_set_color(VGA_YELLOW, VGA_BLACK);
        vga_puts("[MATLAB] ode45 Lorenz: 2847 steps, final=(-4.2,-6.8,23.1)\n");
        vga_set_color(VGA_WHITE, VGA_BLACK);
    } else if (strcmp(args[1], "fft") == 0) {
        vga_set_color(VGA_LIGHT_CYAN, VGA_BLACK);
        vga_puts("[MATLAB] FFT 1024@44.1kHz: 440Hz(A4), SNR=42.3dB, THD=0.12%\n");
        vga_set_color(VGA_WHITE, VGA_BLACK);
    } else if (strcmp(args[1], "eigenvalue") == 0) {
        vga_set_color(VGA_LIGHT_GREEN, VGA_BLACK);
        vga_puts("[MATLAB] Eig 50x50 SPD: min=0.023 max=12.4 cond=539.1\n");
        vga_set_color(VGA_WHITE, VGA_BLACK);
    } else if (strcmp(args[1], "plot") == 0) {
        vga_set_color(VGA_LIGHT_MAGENTA, VGA_BLACK);
        vga_puts("[MATLAB] surf(peak(50)) jet 1920x1080 -> figure1.png\n");
        vga_set_color(VGA_WHITE, VGA_BLACK);
    } else {
        vga_puts("Usage: matlab <workspace|matrix|plot|ode|fft|eigenvalue>\n");
    }
}

static void cmd_scilab59(int argc, char args[][CMD_MAX_LEN]) {
    if (argc < 2) {
        vga_puts("Usage: scilab <workspace|matrix|poly|ode|optim|signal>\n");
        return;
    }
    if (strcmp(args[1], "workspace") == 0) {
        vga_set_color(VGA_LIGHT_GREEN, VGA_BLACK);
        vga_puts("[Scilab] 18 vars, 2.4MB, 42 functions loaded\n");
        vga_set_color(VGA_WHITE, VGA_BLACK);
    } else if (strcmp(args[1], "matrix") == 0) {
        vga_set_color(VGA_LIGHT_CYAN, VGA_BLACK);
        vga_puts("[Scilab] A(200)x .* B: 0.8ms | svd=[12.4..0.002]\n");
        vga_set_color(VGA_WHITE, VGA_BLACK);
    } else if (strcmp(args[1], "poly") == 0) {
        vga_set_color(VGA_YELLOW, VGA_BLACK);
        vga_puts("[Scilab] roots([1 -3 3 -1])=[1,1,1] | poly degree=3\n");
        vga_set_color(VGA_WHITE, VGA_BLACK);
    } else if (strcmp(args[1], "ode") == 0) {
        vga_set_color(VGA_LIGHT_CYAN, VGA_BLACK);
        vga_puts("[Scilab] rk45 Van der Pol mu=1: 1523 steps, max_dt=0.042s\n");
        vga_set_color(VGA_WHITE, VGA_BLACK);
    } else if (strcmp(args[1], "optim") == 0) {
        vga_set_color(VGA_LIGHT_GREEN, VGA_BLACK);
        vga_puts("[Scilab] fminunc Rosenbrock: x*=[1,1], f=0, 42 iters\n");
        vga_set_color(VGA_WHITE, VGA_BLACK);
    } else if (strcmp(args[1], "signal") == 0) {
        vga_set_color(VGA_LIGHT_MAGENTA, VGA_BLACK);
        vga_puts("[Scilab] Butterworth LP order=4 fc=100Hz, fft: 50Hz\n");
        vga_set_color(VGA_WHITE, VGA_BLACK);
    } else {
        vga_puts("Usage: scilab <workspace|matrix|poly|ode|optim|signal>\n");
    }
}

static void cmd_r_project59(int argc, char args[][CMD_MAX_LEN]) {
    if (argc < 2) {
        vga_puts("Usage: R <env|dataframe|ggplot|regression|clustering|ts>\n");
        return;
    }
    if (strcmp(args[1], "env") == 0) {
        vga_set_color(VGA_LIGHT_GREEN, VGA_BLACK);
        vga_puts("[R] 4.3.2 x86_64, 12 pkgs, 45.2MB, 18 objects\n");
        vga_set_color(VGA_WHITE, VGA_BLACK);
    } else if (strcmp(args[1], "dataframe") == 0) {
        vga_set_color(VGA_LIGHT_CYAN, VGA_BLACK);
        vga_puts("[R] mtcars: 32x11, mpg mean=20.1 sd=6.0\n");
        vga_set_color(VGA_WHITE, VGA_BLACK);
    } else if (strcmp(args[1], "ggplot") == 0) {
        vga_set_color(VGA_YELLOW, VGA_BLACK);
        vga_puts("[R] ggplot2: geom_point+smooth, R2=0.753, p=1.29e-10\n");
        vga_set_color(VGA_WHITE, VGA_BLACK);
    } else if (strcmp(args[1], "regression") == 0) {
        vga_set_color(VGA_LIGHT_CYAN, VGA_BLACK);
        vga_puts("[R] lm(mpg~wt+hp+cyl): R2=0.834 F=46.2 p<0.001\n");
        vga_set_color(VGA_WHITE, VGA_BLACK);
    } else if (strcmp(args[1], "clustering") == 0) {
        vga_set_color(VGA_LIGHT_GREEN, VGA_BLACK);
        vga_puts("[R] kmeans K=3: iter=12, between/total=78.4%, sizes=14,10,8\n");
        vga_set_color(VGA_WHITE, VGA_BLACK);
    } else if (strcmp(args[1], "ts") == 0) {
        vga_set_color(VGA_LIGHT_MAGENTA, VGA_BLACK);
        vga_puts("[R] ARIMA(2,1,1): AIC=452.3, Ljung-Box p=0.34\n");
        vga_set_color(VGA_WHITE, VGA_BLACK);
    } else {
        vga_puts("Usage: R <env|dataframe|ggplot|regression|clustering|ts>\n");
    }
}

static void cmd_sas59(int argc, char args[][CMD_MAX_LEN]) {
    if (argc < 2) {
        vga_puts("Usage: sas <proc|dataset|glm|logistic|mixed|sql>\n");
        return;
    }
    if (strcmp(args[1], "proc") == 0) {
        vga_set_color(VGA_LIGHT_GREEN, VGA_BLACK);
        vga_puts("[SAS] 42 procs: MEANS FREQ REG LOGISTIC MIXED GLM\n");
        vga_set_color(VGA_WHITE, VGA_BLACK);
    } else if (strcmp(args[1], "dataset") == 0) {
        vga_set_color(VGA_LIGHT_CYAN, VGA_BLACK);
        vga_puts("[SAS] WORK.TRIAL: 1000 obs x 15 vars, 2.4MB\n");
        vga_set_color(VGA_WHITE, VGA_BLACK);
    } else if (strcmp(args[1], "glm") == 0) {
        vga_set_color(VGA_YELLOW, VGA_BLACK);
        vga_puts("[SAS] GLM: Y=A*B, A(p=0.001) B(p=0.023) R2=0.456\n");
        vga_set_color(VGA_WHITE, VGA_BLACK);
    } else if (strcmp(args[1], "logistic") == 0) {
        vga_set_color(VGA_LIGHT_CYAN, VGA_BLACK);
        vga_puts("[SAS] Logistic: AUC=0.847, Sens=82.3% Spec=78.5%\n");
        vga_set_color(VGA_WHITE, VGA_BLACK);
    } else if (strcmp(args[1], "mixed") == 0) {
        vga_set_color(VGA_LIGHT_GREEN, VGA_BLACK);
        vga_puts("[SAS] Mixed: Var(Subj)=2.34 Var(Err)=5.67, p=0.003\n");
        vga_set_color(VGA_WHITE, VGA_BLACK);
    } else if (strcmp(args[1], "sql") == 0) {
        vga_set_color(VGA_LIGHT_MAGENTA, VGA_BLACK);
        vga_puts("[SAS] PROC SQL: SELECT...GROUP BY...3 rows (0.23s)\n");
        vga_set_color(VGA_WHITE, VGA_BLACK);
    } else {
        vga_puts("Usage: sas <proc|dataset|glm|logistic|mixed|sql>\n");
    }
}
static void cmd_spss59(int argc, char args[][CMD_MAX_LEN]) {
    if (argc < 2) {
        vga_puts("Usage: spss <data|descriptives|ttest|anova|regression|factor>\n");
        return;
    }
    if (strcmp(args[1], "data") == 0) {
        vga_set_color(VGA_LIGHT_GREEN, VGA_BLACK);
        vga_puts("[SPSS] survey.sav: 2500 cases x 42 vars\n");
        vga_set_color(VGA_WHITE, VGA_BLACK);
    } else if (strcmp(args[1], "descriptives") == 0) {
        vga_set_color(VGA_LIGHT_CYAN, VGA_BLACK);
        vga_puts("[SPSS] Age: mean=42.3 sd=12.8 | Income: mean=52400\n");
        vga_set_color(VGA_WHITE, VGA_BLACK);
    } else if (strcmp(args[1], "ttest") == 0) {
        vga_set_color(VGA_YELLOW, VGA_BLACK);
        vga_puts("[SPSS] t(296)=3.92 p<0.001 d=0.46 (independent)\n");
        vga_set_color(VGA_WHITE, VGA_BLACK);
    } else if (strcmp(args[1], "anova") == 0) {
        vga_set_color(VGA_LIGHT_CYAN, VGA_BLACK);
        vga_puts("[SPSS] ANOVA: F(2,297)=8.45 p<0.001 eta2=0.054\n");
        vga_set_color(VGA_WHITE, VGA_BLACK);
    } else if (strcmp(args[1], "regression") == 0) {
        vga_set_color(VGA_LIGHT_GREEN, VGA_BLACK);
        vga_puts("[SPSS] R=0.678 R2=0.460 F(5,294)=49.8 p<0.001\n");
        vga_set_color(VGA_WHITE, VGA_BLACK);
    } else if (strcmp(args[1], "factor") == 0) {
        vga_set_color(VGA_LIGHT_MAGENTA, VGA_BLACK);
        vga_puts("[SPSS] PCA: KMO=0.847, 5 factors, var=68.3%\n");
        vga_set_color(VGA_WHITE, VGA_BLACK);
    } else {
        vga_puts("Usage: spss <data|descriptives|ttest|anova|regression|factor>\n");
    }
}

static void cmd_stata59(int argc, char args[][CMD_MAX_LEN]) {
    if (argc < 2) {
        vga_puts("Usage: stata <summarize|regress|xtreg|ivregress|mergemany|table>\n");
        return;
    }
    if (strcmp(args[1], "summarize") == 0) {
        vga_set_color(VGA_LIGHT_GREEN, VGA_BLACK);
        vga_puts("[Stata] 5000 obs, GDP mean=45200 sd=12800\n");
        vga_set_color(VGA_WHITE, VGA_BLACK);
    } else if (strcmp(args[1], "regress") == 0) {
        vga_set_color(VGA_LIGHT_CYAN, VGA_BLACK);
        vga_puts("[Stata] OLS: ln(wage)~educ+exper R2=0.312 educ coef=0.109\n");
        vga_set_color(VGA_WHITE, VGA_BLACK);
    } else if (strcmp(args[1], "xtreg") == 0) {
        vga_set_color(VGA_YELLOW, VGA_BLACK);
        vga_puts("[Stata] RE: 150 groups x 20 periods, Hausman p=0.12\n");
        vga_set_color(VGA_WHITE, VGA_BLACK);
    } else if (strcmp(args[1], "ivregress") == 0) {
        vga_set_color(VGA_LIGHT_CYAN, VGA_BLACK);
        vga_puts("[Stata] 2SLS: F=42.3(strong IV), Hausman p=0.003\n");
        vga_set_color(VGA_WHITE, VGA_BLACK);
    } else if (strcmp(args[1], "mergemany") == 0) {
        vga_set_color(VGA_LIGHT_GREEN, VGA_BLACK);
        vga_puts("[Stata] Merge: 5000+3200 key=firm_id match=4800(96%)\n");
        vga_set_color(VGA_WHITE, VGA_BLACK);
    } else if (strcmp(args[1], "table") == 0) {
        vga_set_color(VGA_LIGHT_MAGENTA, VGA_BLACK);
        vga_puts("[Stata] Summary: wage educ exper female, N=5000\n");
        vga_set_color(VGA_WHITE, VGA_BLACK);
    } else {
        vga_puts("Usage: stata <summarize|regress|xtreg|ivregress|mergemany|table>\n");
    }
}

static void cmd_jasp59(int argc, char args[][CMD_MAX_LEN]) {
    if (argc < 2) {
        vga_puts("Usage: jasp <bayesian|frequentist|anova|regression|meta|reliability>\n");
        return;
    }
    if (strcmp(args[1], "bayesian") == 0) {
        vga_set_color(VGA_LIGHT_GREEN, VGA_BLACK);
        vga_puts("[JASP] Bayesian t-test: BF10=15.2 HDI=[0.28,0.62]\n");
        vga_set_color(VGA_WHITE, VGA_BLACK);
    } else if (strcmp(args[1], "frequentist") == 0) {
        vga_set_color(VGA_LIGHT_CYAN, VGA_BLACK);
        vga_puts("[JASP] Chi2(3)=12.4 p=0.006, V=0.18\n");
        vga_set_color(VGA_WHITE, VGA_BLACK);
    } else if (strcmp(args[1], "anova") == 0) {
        vga_set_color(VGA_YELLOW, VGA_BLACK);
        vga_puts("[JASP] 2-way: A F(2,117)=8.92 p<0.001 eta2=0.13\n");
        vga_set_color(VGA_WHITE, VGA_BLACK);
    } else if (strcmp(args[1], "regression") == 0) {
        vga_set_color(VGA_LIGHT_GREEN, VGA_BLACK);
        vga_puts("[JASP] Bayes reg: best Y~X1+X3 BF10=23.4 X1:0.52[0.38,0.66]\n");
        vga_set_color(VGA_WHITE, VGA_BLACK);
    } else if (strcmp(args[1], "meta") == 0) {
        vga_set_color(VGA_LIGHT_CYAN, VGA_BLACK);
        vga_puts("[JASP] Meta: 12 studies N=4520 g=0.45[0.31,0.59] I2=34.2%\n");
        vga_set_color(VGA_WHITE, VGA_BLACK);
    } else if (strcmp(args[1], "reliability") == 0) {
        vga_set_color(VGA_LIGHT_MAGENTA, VGA_BLACK);
        vga_puts("[JASP] alpha=0.847 omega=0.862 lambda6=0.831\n");
        vga_set_color(VGA_WHITE, VGA_BLACK);
    } else {
        vga_puts("Usage: jasp <bayesian|frequentist|anova|regression|meta|reliability>\n");
    }
}

static void cmd_jamovi59(int argc, char args[][CMD_MAX_LEN]) {
    if (argc < 2) {
        vga_puts("Usage: jamovi <ttest|anova|regression|contingency|descriptives|pmc>\n");
        return;
    }
    if (strcmp(args[1], "ttest") == 0) {
        vga_set_color(VGA_LIGHT_GREEN, VGA_BLACK);
        vga_puts("[jamovi] t(298)=3.82 p<0.001 d=0.44 CI=[1.14,3.54]\n");
        vga_set_color(VGA_WHITE, VGA_BLACK);
    } else if (strcmp(args[1], "anova") == 0) {
        vga_set_color(VGA_LIGHT_CYAN, VGA_BLACK);
        vga_puts("[jamovi] RM-ANOVA: F(2,198)=12.4 p<0.001 np2=0.11\n");
        vga_set_color(VGA_WHITE, VGA_BLACK);
    } else if (strcmp(args[1], "regression") == 0) {
        vga_set_color(VGA_YELLOW, VGA_BLACK);
        vga_puts("[jamovi] Logistic: Nagelkerke R2=0.201, acc=74.2%\n");
        vga_set_color(VGA_WHITE, VGA_BLACK);
    } else if (strcmp(args[1], "contingency") == 0) {
        vga_set_color(VGA_LIGHT_CYAN, VGA_BLACK);
        vga_puts("[jamovi] Chi2(4)=18.2 p<0.001 Fisher p=0.003\n");
        vga_set_color(VGA_WHITE, VGA_BLACK);
    } else if (strcmp(args[1], "descriptives") == 0) {
        vga_set_color(VGA_LIGHT_GREEN, VGA_BLACK);
        vga_puts("[jamovi] Score: mean=72.4 med=74 sd=12.3 SW=0.987\n");
        vga_set_color(VGA_WHITE, VGA_BLACK);
    } else if (strcmp(args[1], "pmc") == 0) {
        vga_set_color(VGA_LIGHT_MAGENTA, VGA_BLACK);
        vga_puts("[jamovi] PMC: r(X,Y|Z)=0.342 p<0.001\n");
        vga_set_color(VGA_WHITE, VGA_BLACK);
    } else {
        vga_puts("Usage: jamovi <ttest|anova|regression|contingency|descriptives|pmc>\n");
    }
}

static void cmd_pspp59(int argc, char args[][CMD_MAX_LEN]) {
    if (argc < 2) {
        vga_puts("Usage: pspp <descriptives|ttest|regression|crosstab|frequency|compare>\n");
        return;
    }
    if (strcmp(args[1], "descriptives") == 0) {
        vga_set_color(VGA_LIGHT_GREEN, VGA_BLACK);
        vga_puts("[PSPP] N=1200, Income: mean=$48500 med=$42000\n");
        vga_set_color(VGA_WHITE, VGA_BLACK);
    } else if (strcmp(args[1], "ttest") == 0) {
        vga_set_color(VGA_LIGHT_CYAN, VGA_BLACK);
        vga_puts("[PSPP] 1-sample: t(1199)=-2.34 p=0.019 CI=[-2.26,-0.20]\n");
        vga_set_color(VGA_WHITE, VGA_BLACK);
    } else if (strcmp(args[1], "regression") == 0) {
        vga_set_color(VGA_YELLOW, VGA_BLACK);
        vga_puts("[PSPP] OLS: R=0.567 R2=0.321 F(3,1196)=189.2\n");
        vga_set_color(VGA_WHITE, VGA_BLACK);
    } else if (strcmp(args[1], "crosstab") == 0) {
        vga_set_color(VGA_LIGHT_CYAN, VGA_BLACK);
        vga_puts("[PSPP] Chi2(2)=8.45 p=0.015, V=0.084\n");
        vga_set_color(VGA_WHITE, VGA_BLACK);
    } else if (strcmp(args[1], "frequency") == 0) {
        vga_set_color(VGA_LIGHT_GREEN, VGA_BLACK);
        vga_puts("[PSPP] A=45.2% B=28.7% C=15.3% D=10.8% mode=A\n");
        vga_set_color(VGA_WHITE, VGA_BLACK);
    } else if (strcmp(args[1], "compare") == 0) {
        vga_set_color(VGA_LIGHT_MAGENTA, VGA_BLACK);
        vga_puts("[PSPP] ANOVA: F(3,1196)=6.78 p<0.001 Bonferroni 2 sig\n");
        vga_set_color(VGA_WHITE, VGA_BLACK);
    } else {
        vga_puts("Usage: pspp <descriptives|ttest|regression|crosstab|frequency|compare>\n");
    }
}

static void cmd_gretl59(int argc, char args[][CMD_MAX_LEN]) {
    if (argc < 2) {
        vga_puts("Usage: gretl <ols|tsls|arima|heckman|panel|var>\n");
        return;
    }
    if (strcmp(args[1], "ols") == 0) {
        vga_set_color(VGA_LIGHT_GREEN, VGA_BLACK);
        vga_puts("[gretl] OLS: gdp~cons+inv+gov+nx R2=0.967 DW=1.89\n");
        vga_set_color(VGA_WHITE, VGA_BLACK);
    } else if (strcmp(args[1], "tsls") == 0) {
        vga_set_color(VGA_LIGHT_CYAN, VGA_BLACK);
        vga_puts("[gretl] 2SLS: F=38.7(strong), Sargan p=0.42(valid)\n");
        vga_set_color(VGA_WHITE, VGA_BLACK);
    } else if (strcmp(args[1], "arima") == 0) {
        vga_set_color(VGA_YELLOW, VGA_BLACK);
        vga_puts("[gretl] ARIMA(1,1,1): phi=0.45 theta=-0.32 AIC=496.6\n");
        vga_set_color(VGA_WHITE, VGA_BLACK);
    } else if (strcmp(args[1], "heckman") == 0) {
        vga_set_color(VGA_LIGHT_CYAN, VGA_BLACK);
        vga_puts("[gretl] Heckman: N=1500 sel=980, lambda=0.34(sig)\n");
        vga_set_color(VGA_WHITE, VGA_BLACK);
    } else if (strcmp(args[1], "panel") == 0) {
        vga_set_color(VGA_LIGHT_GREEN, VGA_BLACK);
        vga_puts("[gretl] FE: 200 firms x 10yr, Hausman p=0.008, R2w=0.456\n");
        vga_set_color(VGA_WHITE, VGA_BLACK);
    } else if (strcmp(args[1], "var") == 0) {
        vga_set_color(VGA_LIGHT_MAGENTA, VGA_BLACK);
        vga_puts("[gretl] VAR lag=2(BIC): Granger gdp->ltrate(p=0.003)\n");
        vga_set_color(VGA_WHITE, VGA_BLACK);
    } else {
        vga_puts("Usage: gretl <ols|tsls|arima|heckman|panel|var>\n");
    }
}