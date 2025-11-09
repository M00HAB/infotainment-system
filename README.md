# Infotainment System

*A modern in-car infotainment GUI developed with Qt/QML & C++*

## Table of Contents

* [Overview](#overview)
* [Features](#features)
* [Architecture & Technologies](#architecture--technologies)
* [Getting Started](#getting-started)
* [Usage](#usage)
* [Team & Contribution](#team-&-contribution)

---

## Overview

This project implements an infotainment-style system designed for use in vehicles, leveraging Qt/QML for the UI and C++ for backend logic. It supports media playback, location tracking, search functionality, and is built with automotive use-cases in mind.
As part of the broader “ecoDrive”  ecosystem (my graduation project), this front-end can integrate with vehicle data sources (via OBD, CAN, GPS) to provide a cohesive user experience in the car.

---

## Features

* Media controller (play/pause, track search)
* Location management (GPS integration)
* Search interface for media and navigation
* Custom UI design for automotive/navigational environments
* Structured in Qt/QML + C++ for high performance and embedded deployment
* Clean folder structure (assets, controls, layout-screenshots, screens)

---

## Architecture & Technologies

* **Qt 6.8** — UI layer built with QML (files like `MainPage.qml`, `SplashScreens.qml`, `Style.qml`)
* **C++ backend** — classes like `MusicController.cpp/.h`, `LocationManager.cpp/.h`, `SearchManager.cpp/.h`, `backend.cpp/.h`, `main.cpp`
* **Project file** — `ecoDrive.pro` for Qt build system
* **Folder layout**:

  * `assets/` — images, icons, other static resources
  * `controls/` — custom UI controls
  * `layout-screenshots/` — mockups/screenshots of UI layout
  * `screens/` — QML screens for different functions
* Designed to be friendly, with potential integration into an OBD/CAN system and cloud connectivity (aligned with the larger ecoDrive project).

---

## Getting Started

### Prerequisites

* Qt 6.8 (or compatible version)
* C++ compiler supported by Qt (e.g., GCC, MSVC)
* Qt Creator or your preferred IDE supporting Qt/QML development
* (Optional) A device or emulator capable of running Qt applications

### Setup & Build

1. Clone the repository:

   ```bash
   git clone https://github.com/M00HAB/infotainment-system.git
   cd infotainment-system
   ```
2. Open the `ecoDrive.pro` project file in Qt Creator (or `qmake` it from command line).
3. Configure build (select Debug or Release).
4. Build the project.
5. Run the compiled executable — by default it launches the UI (e.g., `main.qml`).

### Running on Embedded/Target Hardware

* Ensure the target environment supports Qt/QML (embedded Linux, Qt-for-Automotive stack, etc.).
* Deploy the built binary and necessary Qt/QML runtime libraries.
* Optionally integrate with vehicle data interfaces (CAN, OBD, GPS) as per the larger EcoDrive ecosystem.

---

## Usage

* On launch, the splash screen is shown (`SplashScreens.qml`).
* Navigate through the UI via the main page (`MainPage.qml`).
* Use the media controller for playing/searching tracks (`MusicController.*`).
* Use the location manager for GPS tracking (`LocationManager.*`).
* Use the search manager for media/navigation search functionality (`SearchManager.*`).
* Customize styling in `Style.qml`.
* Replace assets or layout in the `assets/`, `controls/`, and `screens/` folders to adapt the UI for your vehicle or brand.

---

## Team & Contribution

- **Project Lead:** Mohab  
  - Leading this project as part of the graduation work under the **AMIT Embedded Linux Diploma Scholarship with Orange Digital Center (ODC)**.

- **Team Members:**  
  - Youssef Mahmoud  
  - Seif Eldeen  

- **Contributions:**  
  - Contributions are welcome! To contribute:  
    - Fork the repository  
    - Create a feature branch (e.g., `feature/improve-ui`)  
    - Follow coding conventions:  
      - Well-commented C++ code  
      - Organized QML files  
      - Consistent styling  
    - Add test coverage where possible  
    - Submit a pull request for review 
---


## Contact & Acknowledgements

For questions or feedback, contact me or submit an issue in this repository.
Special thanks to the [AMIT & ODC] and the project supervisor for guidance.
This project is part of the broader ecoDrive initiative aiming for sustainable automotive innovation.

---
