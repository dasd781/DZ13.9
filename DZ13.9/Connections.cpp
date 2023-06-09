#include <stdio.h>
#include "Connections.h"
#define VERYBIGINT 1000000000

Connections::Connections()
{
    for (int i = 0; i < SIZE; i++)
    {
        for (int j = 0; j < SIZE; j++)
        {
            matrix[i][j] = 0;
        }
    }
    peopleCount = 0;
}
// ���������� �������
void Connections::addPeople(string name)
{
    peoples[peopleCount].name = name;
    peopleCount++;
}
// ���������� �����
void Connections::addMeet(int p1, int p2)
{
    matrix[p1][p2] = 1;
    matrix[p2][p1] = 1;
}
// �������� ������������� �����
bool Connections::meetExists(int p1, int p2)
{
    return matrix[p1][p2] > 0;
}

int Connections::getPeopleCount() const
{
    return peopleCount;
}

string Connections::getPeopleName(int index) const
{
    return peoples[index].name;
}

int Connections::findMinWayDFS(int from, int to)
{
    bool visited[SIZE]; // ������ ���������� ������

    for (int i = 0; i < SIZE; i++)
    {
        visited[i] = false;
    }

    int minDistance = VERYBIGINT;

    int currentDistance = 0;

    inner(from, to, visited, minDistance, currentDistance);

    return minDistance;
}

void Connections::inner(int current, int to, bool visited[], int& minDistance, int currentDistance)
{
    if (current == to)
    {
        // ���� ������ � ������� �������, ���������� ������� ���� � �����������
        if (minDistance > currentDistance)
        {
            // ���� ����� ���������� ������, ����������
            minDistance = currentDistance;
            return;
        }
    }
    visited[current] = true; // ��������� ������� ����������
    for (int i = 0; i < SIZE; i++)
    {
        if (meetExists(current, i) && !visited[i])
        {
            // ��������� �������� ��� ���� ������������ ������� ������
            int newDist = currentDistance + matrix[current][i];
            inner(i, to, visited, minDistance, newDist);
        }
    }
    // ��������, ��� ���� ��� �� �������� ��� �������
    visited[current] = false;
}