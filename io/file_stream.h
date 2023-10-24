#pragma once

#include <fstream>
#include <filesystem>

namespace fs = std::filesystem;

#include "shared/io/stream.h"

class InputFileStream : public Stream
{
public:
	InputFileStream(const fs::path& path);
	virtual ~InputFileStream() = default;

public:
	void* data() override;
	const void* data() const override;

	size_t length() const override;

	size_t position();
	size_t position() const override;
	size_t seek(size_t position) override;

	bool is_open() const override;
	bool is_readable() const override;
	bool is_writable() const override;

protected:
	size_t read_data(void* ptr, size_t length) override;
	size_t write_data(const void* ptr, size_t length) override;

private:
	std::ifstream m_file;
	size_t m_file_size;
};

class OutputFileStream : public Stream
{
public:
	OutputFileStream(const fs::path& path);
	virtual ~OutputFileStream() = default;

public:
	void* data() override;
	const void* data() const override;

	size_t length() const override;

	size_t position();
	size_t position() const override;
	size_t seek(size_t position) override;

	bool is_open() const override;
	bool is_readable() const override;
	bool is_writable() const override;

protected:
	size_t read_data(void* ptr, size_t length) override;
	size_t write_data(const void* ptr, size_t length) override;

private:
	std::ofstream m_file;
	size_t m_file_size;
};
