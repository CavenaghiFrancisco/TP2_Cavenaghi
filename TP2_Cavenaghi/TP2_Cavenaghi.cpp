#include <iostream>
#include <vector>
#include "Vector3.h"

Vector3 pointCutCalculator(Vector3 begin, Vector3 end, float height);
float AreaCalculator(Vector3 point0, Vector3 point1, Vector3 point2, float height);

void main() {
    //Definimos los 11 puntos que necesitamos: 8 puntos para el cubo + 3 puntos que formarán la piramide
    const int pointsAmount = 11;
    //Altura a la que el cubo es cortado por un "plano" para formar la pirámide
    float heightCutPoint = 0.2f;

    //Definimos la recta que corta al cubo y crea la piramide
    Vector3 cutCoord = { 0,heightCutPoint,0 };
    //Creamos un array de puntos
    Vector3 points[pointsAmount];

    //Recorremos el array y lo seteamos en 0
    for (int i = 0; i < pointsAmount; i++)     {
        points[i] = Vector3{ 0,0,0 };
    }

    //Definimos nuestros 3 puntos base
    points[0] = { 0,0,0 };
    points[1] = { 1,0.5f,0.5f };
    points[2] = { 0.5f,0.5f,-1 };

    //Normalizamos y realizamos las operaciones necesarias para obtener los lados y que estos tengan el mismo módulo
    points[0] = Vector3Normalize(points[0]);
    points[1] = Vector3Normalize(points[1]);
    points[2] = Vector3Normalize(points[2]);
    points[3] = points[0] + points[1] + points[2];
    points[4] = points[0] + Vector3Normalize((Vector3CrossProduct(points[1], points[2])));
    points[5] = points[4] + points[1];
    points[6] = points[2] + points[4];
    points[7] = points[2] + points[5];
    points[8] = pointCutCalculator(points[0], points[4], heightCutPoint);
    points[9] = pointCutCalculator(points[0], points[1], heightCutPoint);
    points[10] = pointCutCalculator(points[0], points[2], heightCutPoint);

    std::cout << "Se creo un cubo con las siguientes coordenadas:" << std::endl;
    std::cout << std::endl;

    for (int i = 0; i < 8; i++)     {
        std::cout << "Punto " << i << ": (X = " << points[i].x << ", Y = " << points[i].y << ", Z = " << points[i].z << ")." << std::endl;
        std::cout << std::endl;
    }

    std::cout << std::endl;
    std::cout << "El cubo se lo corta horizontalmente en la coordenada (" << cutCoord.x << ", " << cutCoord.y << ", " << cutCoord.z << "), como el centro de corte." << std::endl;
    std::cout << "Formando una piramide en su parte inferior, con coordenadas de corte en:" << std::endl;
    std::cout << std::endl;

    for (int i = 8; i < pointsAmount; i++)     {
        std::cout << "Punto " << i - 8 << ": (X = " << points[i].x << ", Y = " << points[i].y << ", Z = " << points[i].z << ")." << std::endl;
        std::cout << std::endl;
    }

    std::cout << std::endl;
    std::cout << "El area total formada por las caras laterales de la piramide es: " << AreaCalculator(points[8], points[9], points[10], heightCutPoint) << std::endl;
    std::cout << std::endl;
    std::cout << std::endl;
}


//Calculamos los puntos donde el "plano" corta al cubo
Vector3 pointCutCalculator(Vector3 begin, Vector3 end, float height) {
    //Definimos el punto donde se produce el corte en 0
    Vector3 cutPoint = Vector3{ 0,0,0 };
    //Definimos un vector formado por 2 puntos que conforman el principio y el final de la arista que queremos que se corte con el "plano"
    Vector3 vector = end - begin;
    //Definimos el punto final de la arista
    Vector3 point = end;
    //
    float landa = (height - point.y) / vector.y;
    //Le asignamos su correspondiente valor al punto donde se produce el corte
    cutPoint.x = point.x + vector.x * landa;
    cutPoint.z = point.z + vector.z * landa;
    cutPoint.y = height;
    //Devolvemos el valor del punto
    return cutPoint;
}

//Calculamos el area de los lados de la piramide y los sumamos
float AreaCalculator(Vector3 point0, Vector3 point1, Vector3 point2, float height) {
    const int size = 3;
    Vector3 pointsForBases[size];
    float bases[size];
    pointsForBases[0] = point0;
    pointsForBases[1] = point1;
    pointsForBases[2] = point2;
    int k = 0;
    for (int i = 0; i < size; i++)     {
        for (int j = i + 1; j < size; j++)         {
            bases[k] = (pointsForBases[i] - pointsForBases[j]).Magnitude();
            k++;
        }
    }
    float area = 0;
    for (int i = 0; i < size; i++)     {
        area += ((bases[i] * height) / 2);
    }
    return area;
}