// Copyright (c) 2022 by Apex.AI Inc. All rights reserved.
//
// Licensed under the Apache License, Version 2.0 (the "License");
// you may not use this file except in compliance with the License.
// You may obtain a copy of the License at
//
//     http://www.apache.org/licenses/LICENSE-2.0
//
// Unless required by applicable law or agreed to in writing, software
// distributed under the License is distributed on an "AS IS" BASIS,
// WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
// See the License for the specific language governing permissions and
// limitations under the License.
//
// SPDX-License-Identifier: Apache-2.0
#ifndef IOX_HOOFS_POSIX_WRAPPER_NAMED_SEMAPHORE_HPP
#define IOX_HOOFS_POSIX_WRAPPER_NAMED_SEMAPHORE_HPP

#include "iceoryx_hoofs/cxx/expected.hpp"
#include "iceoryx_hoofs/cxx/filesystem.hpp"
#include "iceoryx_hoofs/cxx/optional.hpp"
#include "iceoryx_hoofs/cxx/string.hpp"
#include "iceoryx_hoofs/design_pattern/builder.hpp"
#include "iceoryx_hoofs/internal/posix_wrapper/semaphore_interface.hpp"
#include "iceoryx_hoofs/platform/platform_settings.hpp"
#include "iceoryx_hoofs/posix_wrapper/types.hpp"

namespace iox
{
namespace posix
{
/// @brief A named posix semaphore.
class NamedSemaphore final : public internal::SemaphoreInterface<NamedSemaphore>
{
  public:
    using Name_t = cxx::string<platform::IOX_MAX_PATH_LENGTH>;

    NamedSemaphore(const NamedSemaphore&) noexcept = delete;
    NamedSemaphore(NamedSemaphore&&) noexcept = delete;
    NamedSemaphore& operator=(const NamedSemaphore&) noexcept = delete;
    NamedSemaphore& operator=(NamedSemaphore&&) noexcept = delete;
    ~NamedSemaphore() noexcept;

  private:
    friend class NamedSemaphoreBuilder;
    friend class iox::cxx::optional<NamedSemaphore>;
    friend class internal::SemaphoreInterface<NamedSemaphore>;

    NamedSemaphore(iox_sem_t* handle, const Name_t& name) noexcept;
    iox_sem_t* getHandle() noexcept;

    iox_sem_t* m_handle = nullptr;
    Name_t m_name;
};

class NamedSemaphoreBuilder
{
    /// @brief Defines the semaphore name
    IOX_BUILDER_PARAMETER(NamedSemaphore::Name_t, name, "")

    /// @brief Defines how the semaphore is opened
    IOX_BUILDER_PARAMETER(OpenMode, openMode, OpenMode::OPEN_EXISTING)

    /// @brief Defines the access permissions of the semaphore
    IOX_BUILDER_PARAMETER(cxx::perms, permissions, cxx::perms::none)

    /// @brief Set the initial value of the unnamed posix semaphore
    IOX_BUILDER_PARAMETER(uint32_t, initialValue, 0U)

  public:
    cxx::expected<SemaphoreError> create(cxx::optional<NamedSemaphore>& uninitializedSemaphore) noexcept;
};
} // namespace posix
} // namespace iox

#endif
