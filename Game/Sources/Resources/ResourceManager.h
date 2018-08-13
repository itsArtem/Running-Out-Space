#ifndef RESOURCE_MANAGER_H
#define RESOURCE_MANAGER_H

#include <unordered_map>
#include <iostream>

template<typename Resource> class ResourceManager
{
public:
	void load(const std::string &id, const std::string &path)
	{
		if (has(id))
		{
			std::cerr << "Unable to load \"" << id << "\". Reason: file already loaded.\n";
			return;
		}

		Resource resource;

		if (resource.loadFromFile(path))
			resources.insert(std::make_pair(id, resource));
	}

	bool has(const std::string &id)
	{
		return resources.find(id) != resources.end();
	}

	Resource &get(const std::string &id)
	{
		return resources.at(id);
	}

	void erase(const std::string &id)
	{
		if (!has(id))
		{
			std::cerr << "Unable to erase \"" << id << "\". Reason: file not found.\n";
			return;
		}

		resources.erase(id);
	}


private:
	std::unordered_map<std::string, Resource> resources;
};

#endif