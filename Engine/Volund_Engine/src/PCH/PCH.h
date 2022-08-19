#pragma once

#define _CRT_SECURE_NO_WARNINGS
#define STB_IMAGE_IMPLEMENTATION
#define STB_IMAGE_WRITE_IMPLEMENTATION
#define STB_IMAGE_STATIC
#define STB_IMAGE_WRITE_STATIC
#define GLEW_STATIC

#define VOLUND_START_WINDOWED

#define CONFIG_JSON "Config.json"

#include <iostream>
#include <string>
#include <sstream>
#include <vector>
#include <map>
#include <future>
#include <fstream>
#include <filesystem>
#include <memory>

#include <Include/json/json.hpp>
#include <Include/GLFW/glfw3.h>

#include "Console/Console.h"

using JSON = nlohmann::json;