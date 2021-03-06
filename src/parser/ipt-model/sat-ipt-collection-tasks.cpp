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
#include "sat-ipt-collection.h"
#include "sat-sideband-model.h"
#include <sstream>
#include <fstream>
#include <string>

using namespace sat;

void usage(const char* name)
{
    printf("Usage: %s <collection-file>\n", name);
}

int main(int argc, char* argv[])
{
    if (argc != 2) {
        usage(argv[0]);
        exit(EXIT_FAILURE);
    }

    ifstream input(argv[1]);
    ipt_collection collection(input);

    // build sideband to get mappings from tids to processes and threads
    shared_ptr<sideband_model> sideband{new sideband_model};
    if (!sideband->build(collection.sideband_path())) {
        fprintf(stderr, "sideband model building failed\n");
        exit(EXIT_FAILURE);
    }

    for (auto tid : collection.tids()) {
        pid_t    pid;
        pid_t    thread_id;
        unsigned cpu;
        string   tname = "";
        stringstream ss;
        int thread_id_int;

        if (!tid_get_info(tid, pid, thread_id, cpu)) {
            fprintf(stderr, "could not get pid & thread id for tid %u\n", tid);
            exit(EXIT_FAILURE);
        }
        auto task = collection.task(tid);
        if (task->name().length() == 0) {
            thread_id_int = thread_id;
            ss << "thread-" << thread_id_int;
            tname = ss.str();
        } else {
            tname = task->name();
        }
        cout << tid          << "|"
             << pid          << "|"
             << thread_id    << "|"
             << tname << endl;
    }
}
