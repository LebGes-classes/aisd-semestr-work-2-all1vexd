#include <vector>
#include <iostream>
#include <utility> // ��� pair
#include <queue>
#pragma once

using namespace std;


class Prima
{
public:

    enum vertexes { A, B, C, D, E, vertexes_count }; // ������������ �������� - ��������� ������ 

    const vector<vector<pair<vertexes, int>>> graph = // ������������� ���� (��� ��� �onst)
        // ������ ����� ������������ ����� <���� ����� �����, ��� �����>
    { {{B, 1}, {C, 4}}, // ����� �� ������� A 
    {{A, 1}, {C, 2}, {D, 5}},  // �� B
    {{A, 4}, {B, 2}, {D, 3} }, // �� �
    {{B, 5}, {C, 3} } // �� D
    };

    vector<vector<pair<vertexes, int>>> prima(vertexes start) {/* � �������� ��������� ����� �������� ������� prim
        �������� ��������� ������������ ������� */

        vector <bool> included_vertexes(vertexes_count, false); // ������ ������� == ���������� ������ , ���������� , ����� �� ������� � �����

        priority_queue<pair<int, pair<vertexes, vertexes>>, vector<pair<int, pair<vertexes, vertexes>>>, greater<>> queue;
        /* ��� ������������ ������� , ������� � ������� ����������� greater<> ���������� �������������� ��� ������
        �� ����������� ���� ����������� �� ����� � ����� �������� �� � ��� ���������� ��������� */

        vector<vector<pair<vertexes, int>>> ostov(vertexes_count); // ��� ���� ����� ���������� ���������

        included_vertexes[start] = true; // ����� �������� ��������� ������� � ����� 
        for (const auto& pairs : graph[start]) { // �������� ����� � ������� � ������� start
            queue.push({ pairs.second, {start, pairs.first} }); // std::pair ; ��������� � queue ����� , ��������� �� ��������� �������
        }

        while (!queue.empty()) {
            pair<int, pair<vertexes, vertexes>> topElem = queue.top(); // �������� ����� � ���������� ����� (int)
            int weight = topElem.first; // ��� �����
            pair<vertexes, vertexes> pairs = topElem.second; // ���� ������ 

            queue.pop(); // �������� ���������� ����� c ���������� ����� � ��� ���� ������

            vertexes u = pairs.first; // ��������� �������
            vertexes v = pairs.second; // �������� ������� 
            // ����������� ������ weight

            if (included_vertexes[v]) {
                continue; // ���� �������� ������� ��� ���� � ������ , ��������� � ������ �����
            }

            included_vertexes[v] = true;
            ostov[u].push_back({ v, weight }); // ��������� ����� u - v (v - u)
            ostov[v].push_back({ u, weight });

            for (const auto& pairs : graph[v]) {
                if (!included_vertexes[pairs.first]) {
                    queue.push({ pairs.second, {v, pairs.first} });
                }
            }
        }

        return ostov;
    }

    void run() {

        auto result = prima(C);

        cout << "{\n";
        for (int i = 0; i < vertexes_count; ++i) {
            cout << "    {";
            for (size_t j = 0; j < result[i].size(); ++j) {
                cout << " {" << char('A' + result[i][j].first) << ", " << result[i][j].second << "}";
                if (j < result[i].size() - 1) {
                    cout << ",";
                }
            }
            cout << " }";
            if (i < vertexes_count - 1) {
                cout << ",";
            }
            cout << " // rebra iz verwiny " << char('A' + i) << "\n"; // ��������� ����������� � ��������� ������� 
        }
        cout << "};\n";

    }

};

int main()
{
    Prima prim;
    prim.run();
    return 0;
}