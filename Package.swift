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
                "breakpad/src/client/linux/crash_generation/crash_generation_client.cc",
                "breakpad/src/client/linux/dump_writer_common/thread_info.cc",
                "breakpad/src/client/linux/dump_writer_common/ucontext_reader.cc",
                "breakpad/src/client/linux/handler/exception_handler.cc",
                "breakpad/src/client/linux/handler/minidump_descriptor.cc",
                "breakpad/src/client/linux/log/log.cc",
                "breakpad/src/client/linux/microdump_writer/microdump_writer.cc",
                "breakpad/src/client/linux/minidump_writer/linux_dumper.cc",
                "breakpad/src/client/linux/minidump_writer/linux_ptrace_dumper.cc",
                "breakpad/src/client/linux/minidump_writer/minidump_writer.cc",
                "breakpad/src/client/linux/minidump_writer/pe_file.cc",
                "breakpad/src/client/minidump_file_writer.cc",
                "breakpad/src/common/convert_UTF.cc",
                "breakpad/src/common/md5.cc",
                "breakpad/src/common/string_conversion.cc",
                "breakpad/src/common/linux/breakpad_getcontext.S",
                "breakpad/src/common/linux/elfutils.cc",
                "breakpad/src/common/linux/file_id.cc",
                "breakpad/src/common/linux/guid_creator.cc",
                "breakpad/src/common/linux/linux_libc_support.cc",
                "breakpad/src/common/linux/memory_mapped_file.cc",
                "breakpad/src/common/linux/safe_readlink.cc",
        	],
        	cxxSettings: [
        		.headerSearchPath("./breakpad/src"),
                .headerSearchPath("./breakpad/src/common/android/include"),
                .headerSearchPath("."),
        	]
        )
    ]
)