#include <iostream>
#include <stdlib.h>
#include <fstream>
#include <vector>
#include <time.h>
#include <string>
using namespace std;

bool all_visited(vector<int> visited)
{
	int size = visited.size();
	for (int i = 0; i < size; i++)
	{
		if (visited[i] == 0)
		{
			return false;
		}
	}
	return true;
}

int score(vector<int> vc, vector<vector<int>> &adj_list, int x)
{
	int score = 0;
	for (int i = 0; i < vc.size() - 2; i++)
	{
		if (adj_list[vc[i]][vc[i + 1]] > adj_list[vc[i + 1]][vc[i + 2]])
		{
			score += adj_list[vc[i]][vc[i + 1]] * x;
		}
		else
		{
			score += adj_list[vc[i]][vc[i + 1]];
		}
	}
	score += adj_list[vc[vc.size() - 2]][vc[vc.size() - 1]];
	return score;
}

vector<int> shuffle(vector<int> vc)
{
	int size = vc.size();
	if (size > 1)
	{
		for (int i = 0; i < size; i++)
		{
			int target = i;
			while (target == i)
			{
				target = rand() % size;
			}
			int temp = vc[i];
			vc[i] = vc[target];
			vc[target] = temp;
		}
	}
	return vc;
}

bool not_in_vc(int x, vector<int> &vc)
{
	for (int i = 0; i < vc.size(); i++)
	{
		if (vc[i] == x)
		{
			return false;
		}
	}
	return true;
}

int get_index(vector<int> vc, int num)
{
	int sum = 0;
	for (int i = 0; i < vc.size(); i++)
	{
		sum += vc[i];
		if (sum >= num)
		{
			return i;
		}
	}
}

vector<int> deep_search(vector<int> &visited, vector<vector<int>> &adj_list_indexes, int end, vector<vector<int>> &mones, int iter, int stop)
{
	vector<int> considered;
	vector<int> map;
	considered.push_back(end);
	map.push_back(end);
	for (int i = 0; i < considered.size(); i++)
	{
		if (iter < stop)
		{
			vector<int> shuff = shuffle(adj_list_indexes[considered[i]]);
			for (int j = 0; j < shuff.size(); j++)
			{
				if (not_in_vc(shuff[j], considered))
				{
					considered.push_back(shuff[j]);
					map.push_back(i);
					if (visited[shuff[j]] == 0)
					{
						visited[shuff[j]] = 1;
						goto exit_deep_search;
					}
				}
			}
		}
		else
		{
			vector<int> not_shuff = adj_list_indexes[considered[i]];
			for (int j = 0; j < not_shuff.size(); j++)
			{
				if (mones[considered[i]][not_shuff[j]] == 0 || not_in_vc(not_shuff[j], considered) == false)
				{
					not_shuff.erase(not_shuff.begin() + j);
					j--;
				}
			}
			while (not_shuff.size() > 0)
			{
				int sum = 0;
				for (int j = 0; j < not_shuff.size(); j++)
				{
					if (mones[considered[i]][not_shuff[j]] == 0 || not_in_vc(not_shuff[j], considered) == false)
					{
						not_shuff.erase(not_shuff.begin() + j);
						j--;
					}
					else
					{
						sum = sum + mones[considered[i]][not_shuff[j]];
					}
				}
				int num = rand() % sum;
				for (int j = 0; j < not_shuff.size(); j++)
				{
					num -= mones[considered[i]][not_shuff[j]];
					if (num < 0)
					{
						considered.push_back(not_shuff[j]);
						map.push_back(i);
						if (visited[not_shuff[j]] == 0)
						{
							visited[not_shuff[j]] = 1;
							goto exit_deep_search;
						}
						not_shuff.erase(not_shuff.begin() + j);
						break;
					}
				}
			}
		}
	}
	exit_deep_search:vector<int> solution;
	for (int i = considered.size() - 1; i != 0;)
	{
		solution.push_back(considered[i]);
		i = map[i];
	}
	reverse(solution.begin(), solution.end());
	return solution;
}

int main(int argc, char* argv[])
{
		ofstream outstream;
		outstream.open("none.txt");
		vector<int> best_path;
		int parowanie_sila = 4;
		int exe_time = 60;
		int parowanie_czest = 11;
		int x = 100;
		int n_of_g = 50;
		int stop = 30;
		int ant_num = 50;
		int needed_time = 60;
		int g_size = 100;
		int qualifiers = 4;
		if (argc == 11)
		{
			parowanie_sila = stoi(argv[1]);
			exe_time = stoi(argv[2]);
			parowanie_czest = stoi(argv[3]);
			x = stoi(argv[4]);
			n_of_g = stoi(argv[5]);
			stop = stoi(argv[6]);
			ant_num = stoi(argv[7]);
			needed_time = stoi(argv[8]);
			g_size = stoi(argv[9]);
			qualifiers = stoi(argv[10]);
		}
		srand(time(0));
		for (int graph_number = 1; graph_number <= n_of_g; graph_number++)
		{
			cout << "graph " << graph_number << "\n";
			vector<int> best_ones;
			vector<int> times;
			vector<vector<int>> mones;
			vector<vector<int>> adj_list;
			vector<vector<int>> adj_list_indexes;
			vector<vector<int>> adj_matrix;
			string the_path = "C:/Users/Marcin/source/repos/Graph generator/Graph generator/";
			std::ifstream mystream(the_path + "graph_nr_" + to_string(graph_number) + "_100__15_wi_100_density70.txt");
			if (mystream.is_open())
			{
				string input;
				int graph_size = 0;
				int i = 0;
				int j = 0;
				vector<int> vc;
				mones.push_back(vc);
				adj_matrix.push_back(vc);
				adj_list.push_back(vc);
				adj_list_indexes.push_back(vc);
				while (getline(mystream, input, ' '))
				{
					if (input[0] == '\n')
					{
						vector<int> vc2;
						mones.push_back(vc2);
						adj_list.push_back(vc2);
						adj_list_indexes.push_back(vc2);
						adj_matrix.push_back(vc2);
						j++;
						i = 0;
						input.erase(remove(input.begin(), input.end(), '\n'), input.end());
					}
					if (input.length() > 0)
					{
						int num = stoi(input);
						mones[j].push_back(0);
						adj_matrix[j].push_back(num);
						if (num != 0)
						{
							adj_list[j].push_back(num);
							adj_list_indexes[j].push_back(i);
						}
						i++;
					}


				}
				g_size = j;
				cout << "-------------\n";
			}
			cout << "jest git\n";
			mystream.close();
			int start_time = time(NULL);
			cout << "iter ";
			int iter_num = -1;
			while (time(NULL) - start_time < exe_time)
			{
				iter_num++;
				cout << iter_num << " ";
				vector<vector<int>> paths;
				vector<int> scores;
					for (int ant = 0; ant < ant_num; ant++)
					{
						int start = rand() % g_size;
						vector<int> path;
						path.push_back(start);
						vector<int> visited;
						visited.resize(g_size);
						visited[start] = 1;
						for (int i = 1; i < g_size; i++)
						{
							vector<int> add;
							add = deep_search(visited, adj_list_indexes, path.back(), mones, iter_num, stop);
							path.insert(path.end(), add.begin(), add.end());
						}
						paths.push_back(path);
						scores.push_back(score(path, adj_matrix, x));
					}
				if (iter_num % parowanie_czest == 10)
					for (int i = 0; i < mones.size(); i++)
					{
						for (int j = 0; j < mones[i].size(); j++)
						{
							mones[i][j] = mones[i][j] / parowanie_sila;
						}
					}
				for (int num = 0; num < qualifiers; num++)
				{
					int min_score = scores[0];
					int index = 0;
					for (int i = 0; i < scores.size(); i++)
					{
						if (min_score > scores[i])
						{
							min_score = scores[i];
							index = i;
						}
					}
					vector<int> this_one = paths[index];
					for (int i = 0; i < paths[index].size() - 1; i++)
					{
						mones[this_one[i]][this_one[i + 1]] += 1;
					}
					if (num == 0)
					{
						times.push_back(time(NULL));
						if (iter_num == 0)
						{
							best_path = paths[index];
							best_ones.push_back(scores[index]);
						}
						else if (best_ones.back() > scores[index])
						{
							best_path = paths[index];
							best_ones.push_back(scores[index]);
						}
						else
						{
							best_ones.push_back(best_ones.back());
						}
					}
					paths.erase(paths.begin() + index);
					scores.erase(scores.begin() + index);
				}
			}
			if (outstream.is_open())
			{
				outstream << "Graf" << graph_number << ": " << best_ones[0] << " " << best_ones.back() << "\n";
				for (int i = 0; i < best_ones.size(); i++)
				{
					outstream << exe_time - (time(NULL) - times[i]) << " " << i << " " << best_ones[i] << "\n";
				}
				cout << "The path: ";
				for (int i = 0; i < best_path.size(); i++)
				{
					outstream << best_path[i] << " ";
				}
				outstream << "\n";
			}
			cout << "\n";
			for (int i = 0; i < best_ones.size(); i++)
			{
				cout << i << " - " << exe_time - (time(NULL) - times[i]) << " - " << best_ones[i] << "\n";
			}
			cout << "The path\n";
			for (int i = 0; i < best_path.size(); i++)
			{
				cout << best_path[i] << " ";
			}
			cout << "\n";
		}
		outstream.close();
}