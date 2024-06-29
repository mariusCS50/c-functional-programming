# Functional Programming in C

This project implements a collection of functional programming operations and task-specific functionalities in C. It is a university homework assignment that verifies list manipulation, memory management, and algorithm correctness through a series of unit tests and style checks.

## Features

- **Functional Utilities:**
  Implements higher-order functions such as:
  - [for_each](../../../../../c:/Users/gaibu/Desktop/PCLP2_HW01/src/functional.c) – Applies a function to each element of a list.
  - [map](../../../../../c:/Users/gaibu/Desktop/PCLP2_HW01/src/functional.c) – Creates a new list by applying a transformation to each element.
  - filter – Extracts elements matching a criterion.
  - reduce – Aggregates list data into a single result.

- **Task Implementations:**
  Specific homework tasks include:
  - **Reverse List:** Reverse a list of integers. ([reverse](src/tasks.h))
  - **Create Number Array:** Build an array of numbers where each number contains an integer part, fractional part, and a string representation. ([create_number_array](src/tasks.h))
  - **Student Filtering:** Extract names of students who passed the course. ([get_passing_students_names](src/tasks.h))
  - **Check Bigger Sum:** Verify if the sum of a list of integers meets or exceeds a given value.
  - **Get Even Indexed Strings:** Extract strings from even positions in a list.
  - **Generate Square Matrix:** Create and display a square matrix.

- **Testing and Style Checking:**
  - Unit tests for each functionality are defined and linked in [tests.h](src/tests.h) and executed via the main program.
  - A set of scripts in the [checker](checker) directory enforce coding style and check for common spelling errors in identifiers and comments.

- **Docker Integration:**
  The project includes Docker support for building and running tests in a containerized environment using [local.sh](local.sh).

## File Structure

- **src/**
  Contains the core C source files and headers:
  - main.c – Entry point that reads user input to run tests.
  - functional.c / functional.h – Implementation of functional programming utilities.
  - tasks.c / tasks.h – Implementations of the project tasks.
  - tests.c / tests.h – Unit tests for validating each task.

- **checker/**
  Provides tools for coding style and consistency:
  - checker.sh
  - The cs/ subdirectory includes style checker scripts and a spelling dictionary.

- **Root Files:**
  - [Makefile](Makefile) – Builds the project by invoking the Makefile in the [src](src) directory.
  - [local.sh](local.sh) – Script to run Docker-based builds, tests, or pushes.
  - [assignment.md](assignment.md) – Contains assignment requirements.
  - Dockerfile, install.sh, and related files support containerization and installation.

## Building the Project

From the project root, run the following command to compile the project:

```sh
make build
```

This command changes directory to [src](src) and invokes its Makefile to generate the executable `functional`.

## Running Tests

After building, change into the [src](src) folder and run the main executable:

```sh
cd src
./functional
```

Follow the on-screen instructions by inputting a test name (for example, `filter`, [map](../../../../../c:/Users/gaibu/Desktop/PCLP2_HW01/src/functional.c), or [reverse](../../../../../c:/Users/gaibu/Desktop/PCLP2_HW01/src/tasks.c)). The executable will run the corresponding task’s test and print the results on the terminal.

## Example Usage

To test the filter functionality, run:

```sh
cd src
./functional
filter
```

Output will indicate if the filter task meets the expected behavior according to the unit tests.

## Docker Usage

Use the included Docker support to build and run the project within a container. Instalation prerequisites instructions are in the assignment.pdf file:

```sh
./local.sh checker
```