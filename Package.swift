// swift-tools-version:5.0
// The swift-tools-version declares the minimum version of Swift required to build this package.

import PackageDescription

let package = Package(
    name: "Breakpad",
    products: [
        .library(name: "Breakpad", targets: ["Breakpad"]),
    ],
    dependencies: [],
    targets: [
        .target(
        	name: "Breakpad", 
        	path: "Source/Breakpad",
        	sources: [
        		"breakpad.cpp",
                "client/linux/crash_generation/crash_generation_client.cc",
                "client/linux/dump_writer_common/thread_info.cc",
                "client/linux/dump_writer_common/ucontext_reader.cc",
                "client/linux/handler/exception_handler.cc",
                "client/linux/handler/minidump_descriptor.cc",
                "client/linux/log/log.cc",
                "client/linux/microdump_writer/microdump_writer.cc",
                "client/linux/minidump_writer/linux_dumper.cc",
                "client/linux/minidump_writer/linux_ptrace_dumper.cc",
                "client/linux/minidump_writer/minidump_writer.cc",
                "client/linux/minidump_writer/pe_file.cc",
                "client/minidump_file_writer.cc",
                "common/convert_UTF.cc",
                "common/md5.cc",
                "common/string_conversion.cc",
                "common/linux/breakpad_getcontext.S",
                "common/linux/elfutils.cc",
                "common/linux/file_id.cc",
                "common/linux/guid_creator.cc",
                "common/linux/linux_libc_support.cc",
                "common/linux/memory_mapped_file.cc",
                "common/linux/safe_readlink.cc",
        	],
        	cxxSettings: [
        		.headerSearchPath(".")
        	]
        )
    ]
)