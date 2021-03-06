/*
// Copyright (c) 2015 Intel Corporation
//
// Licensed under the Apache License, Version 2.0 (the "License");
// you may not use this file except in compliance with the License.
// You may obtain a copy of the License at
//
//      http://www.apache.org/licenses/LICENSE-2.0
//
// Unless required by applicable law or agreed to in writing, software
// distributed under the License is distributed on an "AS IS" BASIS,
// WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
// See the License for the specific language governing permissions and
// limitations under the License.
*/
#ifndef SAT_PATH_MAPPER_H
#define SAT_PATH_MAPPER_H

#include <string>

namespace sat {

using namespace std;

class path_mapper {
public:
    // resolve target filesystem path to a host filesystem path
    // - for finding the kernel, use "vmlinux" as target_path
    // - for finding a kernel module, have target_path end in ".ko"
    virtual bool find_file(const string& target_path,
                           string&       host_path,
                           string&       symbols_path) const = 0;
}; // path_mapper

} // sat

#endif // SAT_PATH_MAPPER_H
