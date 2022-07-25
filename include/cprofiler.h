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

#ifdef ENABLE_PERFETTO

#ifndef CPROFILER_H
#define CPROFILER_H

#ifdef __cplusplus
extern "C" {
#endif
    void cprofiler_trace_event_begin(const char*);
    void cprofiler_trace_event_end();

    static inline void cprofiler_cleanup_end(u_int32_t* to_clean) {
        cprofiler_trace_event_end();
    }

    #define CPROFILER_TRACE_EVENT(name) \
    cprofiler_trace_event_begin(name); \
    u_int32_t cprofiler_trace_scoped___LINE__ __attribute__((cleanup(cprofiler_cleanup_end), unused)) = __LINE__;

#ifdef __cplusplus
}
#endif

#endif

#else
    #define CPROFILER_TRACE_EVENT(name) do{} while(0)
#endif