#include "stdafx.h"
#include "Variables.h"

namespace KLab
{
	Variables::Variables(bool main)
		:main(main)
	{
		init_consts();
	};

	Variables::~Variables()
	{
	};

	shared_ptr<Data> Variables::get(const string &name, bool ex)
	{
		auto result = mem.find(name);
		if (result == mem.end())
		{
			if (!ex)
				return nullptr;
			throw CalcException("Variable '" + name + "' not found!");
		}
		return result->second;
	}

	void Variables::init_consts()
	{
		shared_ptr<ComplexNumber<double>> t;
		t = make_shared<ComplexNumber<double>>(3.141592653589793238462643383279);
		t->_temp = false;
		mem["pi"] = t;

		t = make_shared<ComplexNumber<double>>(2.71828182846);
		t->_temp = false;
		mem["e"] = t;
	}

	void Variables::clear(const string &name)
	{
		if (mem.erase(name) > 0)
			removed.push_back(name);
	}

	void Variables::clear()
	{
		for (auto i = mem.begin(); i != mem.end();)
		{
			removed.push_back(i->first);
			i = mem.erase(i);
		}
		init_consts();
	}

	variables_map_iter Variables::getIterator(const string &name, bool ex)
	{
		auto result = mem.find(name);
		if (result == mem.end() && ex)
			throw CalcException("Variable '" + name + "' not found!");
		return result;
	}

	variables_map_pair Variables::set(const string &name,
		const shared_ptr<Data> &data)
	{
		/* Je¿eli obiekt nie jest tymczasowy,
		   skopiowanie jego wartoœci */
		shared_ptr<Data> temp = data->_temp ? data : data->copy();

		/* Zapis do aktualnej przestrzeni roboczej */
		auto result = mem.insert({ name, temp });

		/* Je¿eli zmienna ju¿ istnieje*/
		if (result.second == false)
		{
			/* Zaktualizowanie jej wartoœci */
			result.first->second = temp;
			temp->_updated = true;
		}
		else
			temp->_added = true;

		/* Zapisany obiekt nie jest ju¿ wartoœci¹
		   tymczasow¹ */
		temp->_temp = false;
		return result;
	}

	void Variables::getUpdated(vector<VariableInfo> &added, vector<VariableInfo> &updated) const
	{
		added.clear();
		updated.clear();
		for (const auto &element : mem)
		{
			if (element.second->_added)
			{
				added.push_back(VariableInfo(element.first, element.second));
			}
			else if (element.second->_updated)
			{
				updated.push_back(VariableInfo(element.first, element.second));
			}
			element.second->_updated = false;
			element.second->_added = false;
		}
	}

	vector<string> Variables::getRemoved()
	{
		return removed;
	}

	void Variables::clearRemoved()
	{
		removed.clear();
	}

	void Variables::menage(const string &operation, const string &working_dir, vector<shared_ptr<Data>> &args)
	{
		if (operation == "clear")
			remove(args);
		else if (operation == "save")
			safe_to_file(working_dir, args);
	}

	void Variables::remove(vector<shared_ptr<Data>> &args)
	{
		if (args.size() == 0)
		{
			clear();
			return;
		}

		for (const shared_ptr<Data> &ptr : args)
		{
			clear(ptr->toString());
		}
	}

	void Variables::safe_to_file(const string &working_dir, vector<shared_ptr<Data>> &args)
	{
		if (args.size() == 0)
			throw CalcException("Too few arguments for 'save' command!");

		int idx = 0;
		for (const auto &i : args)
		{
			if (idx++&&mem.find(i->toString()) == mem.end())
				throw CalcException("'save' command: variable '" + i->toString() + "' not found!");
		}

		std::ofstream file;
		file.open(working_dir + args[0]->toString() + ".klab");

		if (args.size() == 1)
		{
			for (auto i = mem.begin(); i != mem.end(); i++)
				file << i->first << "=" << i->second->toStringCommpact() << ";\n";
		}
		else
			safe_to_file(file, args);
		file.close();
	}

	void Variables::safe_to_file(std::ofstream &file, vector<shared_ptr<Data>> &args)
	{
		for (auto i = args.begin() + 1; i != args.end(); i++)
		{
			/* Checked before if variable exists */
			auto result = mem.find((*i)->toString());
			file << result->first << "=" << result->second->toStringCommpact() << ";\n";
		}
	}
}