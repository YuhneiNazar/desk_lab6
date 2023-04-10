#include "pch.h"
#include "CppUnitTest.h"
#include "../desk_lab6/desk_lab6.cpp"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace UnitTest1
{
	TEST_CLASS(UnitTest1)
	{
	public:
		
		TEST_METHOD(TestMethod1)
		{
			string fname = "test_graph.txt";
			ofstream file(fname);
			file << "4 4\n1 2\n1 3\n2 3\n3 4\n";
			file.close();
			initGraph(fname);
			Assert::AreEqual(4, vertices);
			Assert::AreEqual(4, edges);
		}
		TEST_METHOD(TestMethod2)
		{
			string line = "1 2";
			int lineNumber = 0;
			makeIncidenceMatrix(line, lineNumber);
			Assert::AreEqual(-1, incidence[0][lineNumber]);
			Assert::AreEqual(1, incidence[1][lineNumber]);
		}

		TEST_METHOD(TestMethod3)
		{
			adjacency[0][0] = 0;
			adjacency[0][1] = 0;
			adjacency[1][0] = 0;
			adjacency[1][1] = 0;

			makeAdjacencyMatrix("1 2");
			makeAdjacencyMatrix("2 1");
			makeAdjacencyMatrix("2 2");

			Assert::AreEqual(0, adjacency[0][0]);
			Assert::AreEqual(1, adjacency[0][1]);
			Assert::AreEqual(1, adjacency[1][0]);
			Assert::AreEqual(1, adjacency[1][1]);
		}

		TEST_METHOD(TestMethod4)
		{
			string matrix = "1 0 1\n0 1 0\n1 0 1\n";
			string filePath = "test_matrix.txt";
			saveMatrixToFile(matrix, filePath);
			ifstream inputFile(filePath);
			stringstream buffer;
			buffer << inputFile.rdbuf();
			inputFile.close();
			Assert::AreEqual(matrix, buffer.str());
		}
	};
}
