# Hospital management — data structures practice (C++)

**English** · [Español](README.es.md)

> **Status: incomplete.** The main logic is written in `lib.cpp`, but `main()` does not use it yet
> (it only prints a message), and the tests are still the two example tests from the course
> template.

A hospital management system in C++, written for the **Algorithms and Data Structures 1** course
at UDIT (Madrid), December 2025. The goal of the assignment is to practise **linear data
structures**: lists, queues, priority queues and stacks, plus recursion.

## What is implemented

The classes and operations in `ProyectoAED1/lib.h` and `lib.cpp`:

- **`Hospital`** — manages doctors, patients and the medicine store.
- **`Paciente`** (patient) — with diseases, an urgency priority and a treatment history.
- **`Doctor`** — with a queue of pending cases.
- **`Enfermedad`** (disease) — with lethality and urgency levels.
- **`Medicamento`** (medicine) — stock control and restocking.
- Patient treatment by priority, and a recursive billing calculation.
- Sample data in CSV files (`doctores.csv`, `enfermedades.csv`, `medicamentos.csv`, `pacientes.csv`).

## What is missing

- A menu in `main()` that connects the logic and the CSV loading.
- Real unit tests for each operation (the project is already set up for Google Test).
- Some cleanup from the course template (`TODO` comments, and a `.cpp` file included with
  `#include`).

## Build

You need CMake 3.14+ and a C++11 (or newer) compiler. CMake downloads Google Test automatically.

```bash
cd ProyectoAED1
mkdir build && cd build
cmake ..
make
./ProyectoAED1
```

## Author

Andrea Ávila — [@Andreavilaro0](https://github.com/Andreavilaro0)

## License

Academic project.
