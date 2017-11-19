// OpenCppCoverage is an open source code coverage for C++.
// Copyright (C) 2017 OpenCppCoverage
//
// This program is free software: you can redistribute it and/or modify
// it under the terms of the GNU General Public License as published by
// the Free Software Foundation, either version 3 of the License, or
// any later version.
//
// This program is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
// GNU General Public License for more details.
//
// You should have received a copy of the GNU General Public License
// along with this program.  If not, see <http://www.gnu.org/licenses/>.

#pragma once

#include "DebugInformationEnumerator.hpp"
#include <memory>

namespace boost
{
	namespace filesystem
	{
		class path;
	}
}

namespace FileFilter
{
	class LineInfo;
	class ModuleInfo;
}

namespace CppCoverage
{
	class ICoverageFilterManager;
	class BreakPoint;
	class ExecutedAddressManager;

	class MonitoredLineRegister : private IDebugInformationHandler
	{
	  public:
		MonitoredLineRegister(std::shared_ptr<BreakPoint>,
		                      std::shared_ptr<ExecutedAddressManager>,
		                      std::shared_ptr<ICoverageFilterManager>);

		void RegisterLineToMonitor(const boost::filesystem::path& modulePath,
		                           HANDLE hProcess,
		                           void* baseOfImage);

	  private:
		bool IsSourceFileSelected(const boost::filesystem::path&) override;
		void OnSourceFile(const boost::filesystem::path&,
		                  const std::vector<Line>&) override;
		const FileFilter::ModuleInfo& GetModuleInfo() const;

		std::unique_ptr<FileFilter::ModuleInfo> moduleInfo_;
		const std::shared_ptr<BreakPoint> breakPoint_;
		const std::shared_ptr<ExecutedAddressManager> executedAddressManager_;
		const std::shared_ptr<ICoverageFilterManager> coverageFilterManager_;
	};
}
