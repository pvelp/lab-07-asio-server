//
// Created by pvelp on 3/14/22.
//
#include "logging.hpp"

//void set_logs(size_t val){
//  auto trace_log = logs::add_file_log(
//      keywords::file_name = "../logs_files/log_file_%N",
//      keywords::rotation_size = val*1024*1024,
//      keywords::format = "[%TimeStamp%][%ThreadID%]: %Message%");
//  trace_log->set_filter(logs::trivial::severity >= logs::trivial::trace);
//  auto console_log = logs::add_console_log(
//      std::clog,
//      keywords::format = "[%TimeStamp%][%ThreadID%]: %Message%");
//  console_log->set_filter(logs::trivial::severity >= logs::trivial::trace);
//}

void init(size_t size) {
  boost::shared_ptr< boost::log::core > core = boost::log::core::get();

  boost::shared_ptr< sinks::text_file_backend > backend =
      boost::make_shared< sinks::text_file_backend >(
          keywords::file_name = "./logs_files/log_file_%N",
          keywords::rotation_size = size * 1024 * 1024,
          keywords::format = "[%TimeStamp%]: %Message%",
          keywords::time_based_rotation =
              sinks::file::rotation_at_time_point(12, 0, 0));

  typedef sinks::synchronous_sink< sinks::text_file_backend > sink_t;
  boost::shared_ptr< sink_t > sink(new sink_t(backend));
  //sink ->set_filter(logging::trivial::severity >= logging::trivial::info);
  core->add_sink(sink);
}
