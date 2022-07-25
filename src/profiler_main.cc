/*************************************************************************/
/* Copyright (c) 2022 Nolan Consulting Limited.                          */
/*                                                                       */
/* Permission is hereby granted, free of charge, to any person obtaining */
/* a copy of this software and associated documentation files (the       */
/* "Software"), to deal in the Software without restriction, including   */
/* without limitation the rights to use, copy, modify, merge, publish,   */
/* distribute, sublicense, and/or sell copies of the Software, and to    */
/* permit persons to whom the Software is furnished to do so, subject to */
/* the following conditions:                                             */
/*                                                                       */
/* The above copyright notice and this permission notice shall be        */
/* included in all copies or substantial portions of the Software.       */
/*                                                                       */
/* THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND,       */
/* EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF    */
/* MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT.*/
/* IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY  */
/* CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT,  */
/* TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE     */
/* SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.                */
/*************************************************************************/


#define LOG_TAG "FoxusProfiler"

#include "profiler.h"
#include "cprofiler.h"
#include <atomic>

PERFETTO_TRACK_EVENT_STATIC_STORAGE();

static std::atomic_bool profiler_inited{false};

void profiler_init() {
    bool tst = false;
    if (!profiler_inited.compare_exchange_strong(tst, true)) {
        return;
    }
    perfetto::TracingInitArgs args;
    args.shmem_size_hint_kb = 32768;
    args.shmem_page_size_hint_kb = 8;
    args.backends = perfetto::kSystemBackend;

    perfetto::Tracing::Initialize(args);
    perfetto::TrackEvent::Register();
}

void cprofiler_trace_event_begin(const char* name) {
    TRACE_EVENT_BEGIN("c_profiler", nullptr, [&](perfetto::EventContext ctx) {
        ctx.event()->set_name(name);
    });
}

void cprofiler_trace_event_end() {
    TRACE_EVENT_END("c_profiler");
}