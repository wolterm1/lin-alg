<<<<<<< HEAD
# Matrix/LinAlg
######Hallo
=======
# linAlg
Ein C++-Projekt zur Demonstration grundlegender Operationen aus der linearen Algebra — insbesondere auf Matrizen. Der Fokus liegt auf der manuellen Implementierung mathematischer Operationen zur besseren Nachvollziehbarkeit.

## 📌 Inhalt

Dieses Projekt umfasst:
- Matrixklasse:
  - Matrixaddition
  - Matrixmultiplikation
  - Transposition
  - Berechnung der Determinante
  - Invertierung von Matrizen
  - Lösen linearer Gleichungssysteme
  - Iterator für Kompatibilität mit STL-Algorithmen
- Vektorklasse
- Matrix-Vektor-Multiplikation

## 🧠 Motivation

Dieses Projekt dient dem Verständnis und dem Üben von C++ und linearen Algebra-Konzepten. Der Code ist nicht optimiert und gilt nur dem Interesse, theoretischen Grundlagen praktisch umzusetzen.

## ⚙️ Build & Installation

### Voraussetzungen

- CMake ≥ 3.12
- C++20-kompatible Compiler ❗

### Build-Schritte

```bash
git clone https://github.com/wolterm1/linAlg.git
cd linAlg
mkdir build
cd build
cmake -S . -B build
cmake --build build
