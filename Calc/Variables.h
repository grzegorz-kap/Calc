#ifndef VARIABLES_H
#define VARIABLES_H
#pragma once
#include <map>
#include <string>
#include <memory>
#include <vector>
#include <iostream>
#include <fstream>
#include "Data.h"
#include "VariableInfo.h"
using std::string;
using std::map;
using std::vector;
using std::shared_ptr;
namespace PR
{
	typedef map<string, shared_ptr<Data>> variables_map;
	typedef variables_map::iterator variables_map_iter;
	typedef std::pair<variables_map_iter, bool> variables_map_pair;
	typedef vector<variables_map_pair> AssignmentsData;

	class Variables
	{
		variables_map mem;
		bool main;
		vector<string> removed;
	public:
		Variables(bool main = false);
		~Variables();

		shared_ptr<Data> get(const string &name, bool ex = true);
		void clear();
		void clear(const string &name);
		variables_map_iter getIterator(const string &name, bool ex = true);
		variables_map_pair set(const string &name, const shared_ptr<Data> &data);	
		void menage(const string &operation, const string &working_dir, vector<shared_ptr<Data>> &args);
		void getUpdated(vector<VariableInfo> &added, vector<VariableInfo> &updated) const;
		vector<string> getRemoved();
		void clearRemoved();
	private:
		void remove(vector<shared_ptr<Data>> &args);
		void safe_to_file(const string &working_dir, vector<shared_ptr<Data>> &args);
		void safe_to_file(std::ofstream &file, vector<shared_ptr<Data>> &args);
	};
}
#endif