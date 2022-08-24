#pragma once
#include <malloc.h>
#include <filesystem>
#include <boost/process.hpp>
#include <boost/asio.hpp>

namespace bp = boost::process;
namespace asio = boost::asio;
namespace fs = std::filesystem;


class NodeProcess
{
public:
	NodeProcess() = default;
	NodeProcess(const NodeProcess&) = delete;
	NodeProcess& operator=(const NodeProcess&) = delete;
	void run();
	void terminate();
private:
	fs::path getExeDir();
	bp::child* nodeProcess;
};

