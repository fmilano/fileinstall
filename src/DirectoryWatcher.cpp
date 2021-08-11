/*=============================================================================

  Library: CppMicroServices

  Copyright (c) The CppMicroServices developers. See the COPYRIGHT
  file at the top-level directory of this distribution and at
  https://github.com/CppMicroServices/CppMicroServices/COPYRIGHT .

  Licensed under the Apache License, Version 2.0 (the "License");
  you may not use this file except in compliance with the License.
  You may obtain a copy of the License at

    http://www.apache.org/licenses/LICENSE-2.0

  Unless required by applicable law or agreed to in writing, software
  distributed under the License is distributed on an "AS IS" BASIS,
  WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
  See the License for the specific language governing permissions and
  limitations under the License.

=============================================================================*/

#include <chrono>
#include <filesystem>
#include <iostream>
#include <set>

#include "DirectoryWatcher.h"

namespace cppmicroservices {

using namespace std::chrono_literals;

DirectoryWatcher::DirectoryWatcher() {}

void DirectoryWatcher::Start()
{
  m_stopSignaled = false;
  m_thread = std::thread(&DirectoryWatcher::Run, this);
}

void DirectoryWatcher::Stop()
{
  m_stopSignaled = true;
  m_thread.join();
}

void DirectoryWatcher::Run()
{
  try {
    std::set<std::filesystem::path> previous_files;
    std::set<std::filesystem::path> current_files;

    const std::filesystem::path watched_dir{ "/home/federico/work/test/" };

    while (!m_stopSignaled) {

      for (auto const& dir_entry :
           std::filesystem::directory_iterator{ watched_dir }) {

        if (dir_entry.is_regular_file()) {
          current_files.insert(dir_entry.path());
        }
      }

      for (auto const& curr_file : current_files) {
        if (previous_files.count(curr_file) == 0)
        {
          std::cout << "New file " << curr_file << '\n';
        }
      }

      for (auto const& prev_file : previous_files) {
        if (current_files.count(prev_file) == 0)
        {
          std::cout << "Deleted file " << prev_file << '\n';
        }
      }

      previous_files = current_files;
      current_files.clear();

      std::this_thread::sleep_for(400ms);
    }
  } catch (const std::exception& e) {
    std::cerr << e.what() << '\n';
  } catch (...) {
    std::cerr << "An unexpected exception occurred.\n";
  }
}

}