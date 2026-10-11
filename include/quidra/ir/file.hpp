#pragma once

// Typed-IR instructions of the file domain (files and file handles).
//
// Owns: the domain's instruction structs and their InstructionTraits
// specializations (quidra/ir/domain.hpp). The fields, their order and their
// default member initializers are the IR data model.

#include "quidra/ir/domain.hpp"
#include "quidra/ir/value_id.hpp"
#include "quidra/types.hpp"

#include <cstdint>

namespace quidra::ir {

struct FileOpen { ValueId out; ValueId path; Type result_type; std::uint32_t line{}; std::uint32_t column{}; };
struct FileCreate { ValueId out; ValueId path; Type result_type; std::uint32_t line{}; std::uint32_t column{}; };
struct FileAppend { ValueId out; ValueId path; Type result_type; std::uint32_t line{}; std::uint32_t column{}; };
struct FileHandleRead { ValueId out; ValueId handle; Type result_type; std::uint32_t line{}; std::uint32_t column{}; };
struct FileHandleReadLine { ValueId out; ValueId handle; Type result_type; std::uint32_t line{}; std::uint32_t column{}; };
struct FileHandleReadBin { ValueId out; ValueId handle; Type result_type; std::uint32_t line{}; std::uint32_t column{}; };
struct FileHandleWrite { ValueId out; ValueId handle; ValueId text; Type result_type; bool newline{}; std::uint32_t line{}; std::uint32_t column{}; };
struct FileHandleFlush { ValueId out; ValueId handle; Type result_type; std::uint32_t line{}; std::uint32_t column{}; };
struct FileHandleSeek { ValueId out; ValueId handle; ValueId position; Type result_type; std::uint32_t line{}; std::uint32_t column{}; };
struct FileHandleClose { ValueId handle; };
struct FileRead { ValueId out; ValueId path; Type result_type; std::uint32_t line{}; std::uint32_t column{}; };
struct FileReadBin { ValueId out; ValueId path; Type result_type; std::uint32_t line{}; std::uint32_t column{}; };
struct FileWrite { ValueId out; ValueId path; ValueId text; Type result_type; std::uint32_t line{}; std::uint32_t column{}; };
struct FileWriteBin { ValueId out; ValueId path; ValueId bin; Type result_type; std::uint32_t line{}; std::uint32_t column{}; };
struct FileExists { ValueId out; ValueId path; Type result_type; std::uint32_t line{}; std::uint32_t column{}; };
struct FileIsDirectory { ValueId out; ValueId path; Type result_type; std::uint32_t line{}; std::uint32_t column{}; };
struct FileRemove { ValueId out; ValueId path; Type result_type; std::uint32_t line{}; std::uint32_t column{}; };
struct FileCopy { ValueId out; ValueId source; ValueId destination; Type result_type; std::uint32_t line{}; std::uint32_t column{}; };
struct FileMove { ValueId out; ValueId source; ValueId destination; Type result_type; std::uint32_t line{}; std::uint32_t column{}; };
struct FileMkdir { ValueId out; ValueId path; Type result_type; std::uint32_t line{}; std::uint32_t column{}; };
struct FileList { ValueId out; ValueId path; ValueId recursive; Type result_type; std::uint32_t line{}; std::uint32_t column{}; };

template <> struct InstructionTraits<FileOpen> : InDomain<Domain::file> {};
template <> struct InstructionTraits<FileCreate> : InDomain<Domain::file> {};
template <> struct InstructionTraits<FileAppend> : InDomain<Domain::file> {};
template <> struct InstructionTraits<FileHandleRead> : InDomain<Domain::file> {};
template <> struct InstructionTraits<FileHandleReadLine> : InDomain<Domain::file> {};
template <> struct InstructionTraits<FileHandleReadBin> : InDomain<Domain::file> {};
template <> struct InstructionTraits<FileHandleWrite> : InDomain<Domain::file> {};
template <> struct InstructionTraits<FileHandleFlush> : InDomain<Domain::file> {};
template <> struct InstructionTraits<FileHandleSeek> : InDomain<Domain::file> {};
template <> struct InstructionTraits<FileHandleClose> : InDomain<Domain::file> {};
template <> struct InstructionTraits<FileRead> : InDomain<Domain::file> {};
template <> struct InstructionTraits<FileReadBin> : InDomain<Domain::file> {};
template <> struct InstructionTraits<FileWrite> : InDomain<Domain::file> {};
template <> struct InstructionTraits<FileWriteBin> : InDomain<Domain::file> {};
template <> struct InstructionTraits<FileExists> : InDomain<Domain::file> {};
template <> struct InstructionTraits<FileIsDirectory> : InDomain<Domain::file> {};
template <> struct InstructionTraits<FileRemove> : InDomain<Domain::file> {};
template <> struct InstructionTraits<FileCopy> : InDomain<Domain::file> {};
template <> struct InstructionTraits<FileMove> : InDomain<Domain::file> {};
template <> struct InstructionTraits<FileMkdir> : InDomain<Domain::file> {};
template <> struct InstructionTraits<FileList> : InDomain<Domain::file> {};

} // namespace quidra::ir
