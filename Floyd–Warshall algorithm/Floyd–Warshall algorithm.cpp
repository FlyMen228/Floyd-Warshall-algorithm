#include <iostream>
#include <fstream>
#include <vector>
#include <algorithm>

int const inf = INT_MAX - 100;

std::vector <std::vector <int> > inputAdjacencyMatrixFromFile()
{
    std::ifstream reader("input.txt");
    if (reader.is_open())
    {
        int numOfVertexes;
        reader >> numOfVertexes;
        std::vector < std::vector <int > > adjacencyMatrix(numOfVertexes, std::vector <int>(numOfVertexes));
        for (int i = 0; i < numOfVertexes; ++i)
            for (int j = 0; j < numOfVertexes; ++j)
                if (!reader.eof())
                {
                    reader >> adjacencyMatrix[i][j];
                    if (adjacencyMatrix[i][j] == 0)
                        adjacencyMatrix[i][j] = inf;
                }
                else
                    break;
        reader.close();
        return adjacencyMatrix;
    }
    else
    {
        reader.close();
        std::cout << "File alert!!!!!";
        std::exit(1);
    }
}

void floydWarshallAlgorithm(std::vector <std::vector <int> > adjacencyMatrix)
{
    int demensionOfMatrix = adjacencyMatrix.size();
    for (int k = 0; k < demensionOfMatrix; ++k)
        for (int i = 0; i < demensionOfMatrix; ++i)
            for (int j = 0; j < demensionOfMatrix; ++j)
                //adjacencyMatrix[i][j] = std::min(adjacencyMatrix[i][j], adjacencyMatrix[k][j] + adjacencyMatrix[i][k]);
                if (adjacencyMatrix[i][j] > adjacencyMatrix[k][j] + adjacencyMatrix[i][k])
                    adjacencyMatrix[i][j] = adjacencyMatrix[k][j] + adjacencyMatrix[i][k];
}

void saveAdjacencyMatrixToFile(std::vector <std::vector <int> > adjacencyMatrix)
{
    std::ofstream writer;
    writer.open("output.txt", std::ios_base::out);
    for (int i = 0; i < adjacencyMatrix.size(); ++i)
    {
        for (int j = 0; j < adjacencyMatrix.size(); ++j)
            if (adjacencyMatrix[i][j] < inf)
                writer << adjacencyMatrix[i][j] << " ";
            else
                writer << "INF ";
        writer << std::endl;
    }
    writer.close();
    std::cout << "Saving to file finished successfully!";
}

int main()
{
    std::vector <std::vector <int> > adjancencyMatrix = inputAdjacencyMatrixFromFile();
    floydWarshallAlgorithm(adjancencyMatrix);
    saveAdjacencyMatrixToFile(adjancencyMatrix);
    return 0;
}