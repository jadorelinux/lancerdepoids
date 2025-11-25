#include <iostream>
#include <vector>
#include <cmath>
#include <algorithm>
#include "matplotlibcpp.h"

namespace plt = matplotlibcpp;
using namespace std;

int main() {
    const double g = 9.81;
    const double PI = 3.14159265358979323846;

    cout << "=== Simulateur de lancer de poids (sans vent) ===" << endl;

    double v0, theta;
    cout << "Entrez la vitesse initiale du lancer (m/s) : ";
    cin >> v0;
    cout << "Entrez l'angle de tir (degrés) : ";
    cin >> theta;

    // Conversion en radians
    double theta_rad = theta * (PI / 180.0);

    // Temps total et hauteur max
    double t_total = 2 * v0 * sin(theta_rad) / g;
    double hauteur_max = (pow(v0, 2) * pow(sin(theta_rad), 2)) / (2 * g);

    // Données du mouvement
    vector<double> x, y, t;
    int n = 200;

    for (int i = 0; i <= n; ++i) {
        double ti = i * t_total / n;
        double xi = v0 * cos(theta_rad) * ti;
        double yi = v0 * sin(theta_rad) * ti - 0.5 * g * ti * ti;

        if (yi < 0) yi = 0; // éviter valeurs négatives après impact

        x.push_back(xi);
        y.push_back(yi);
        t.push_back(ti);
    }

    // Taille et style de la figure
    plt::figure_size(900, 500);
    plt::title("Trajectoire du lancer de poids (avec chronomètre)");
    plt::xlabel("Distance horizontale (m)");
    plt::ylabel("Hauteur (m)");
    plt::xlim(-1.0, x.back() * 1.1);
    plt::ylim(0.0, hauteur_max * 1.3);
    plt::grid(true);

    vector<double> x_dyn, y_dyn;

    for (size_t i = 0; i < x.size(); ++i) {
        plt::clf();

        // Tracé dynamique
        x_dyn.push_back(x[i]);
        y_dyn.push_back(y[i]);
        plt::plot(x_dyn, y_dyn, "b-");

        // Point du projectile
        plt::scatter(vector<double>{x[i]}, vector<double>{y[i]}, 50.0);

        // Décor
        plt::axhline(0.0, 0.0, x.back() * 1.1);
        plt::text(-1.0, 0.5, "Lanceur");

        // Chronomètre
        string chrono_text = "t = " + to_string(t[i]).substr(0, 4) + " s";
        plt::text(0.75 * x.back(), hauteur_max * 1.2, chrono_text);

        // Réglages généraux
        plt::title("Trajectoire du lancer de poids (avec chronomètre)");
        plt::xlabel("Distance horizontale (m)");
        plt::ylabel("Hauteur (m)");
        plt::xlim(-1.0, x.back() * 1.1);
        plt::ylim(0.0, hauteur_max * 1.3);
        plt::grid(true);

        plt::pause(0.02);
    }

    plt::show();
    return 0;
}
