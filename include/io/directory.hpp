/*
 * Copyright 2018 Justas Masiulis
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *     http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */

#pragma once
#include "base_file.hpp"

namespace ntw::io {

    template<class Handle>
    struct directory_traits {
        using handle_type  = Handle;
        using options_type = file_options;

        constexpr static auto options =

            NT_FN static open(void*&              handle,
                              OBJECT_ATTRIBUTES&  attributes,
                              const options_type& options,
                              unsigned long       disposition);
    };

    template<class Handle, class Traits = directory_traits<Handle>>
    class basic_directory : public detail::base_file<Traits> {
        using base_type = detail::base_file<Traits>;

    public:
        NTW_INLINE basic_directory() = default;

        template<class ObjectHandle>
        NTW_INLINE basic_directory(const ObjectHandle& handle)
            : base_type(unwrap_handle(handle))
        {}

        template<std::size_t StaticBufferSize = 2048, class Callback, class... Args>
        NT_FN enum_contents(Callback&& cb, Args&&... args) const noexcept;

        template<class Callback, class... Args>
        NT_FN
        enum_contents(void* buffer_begin, void* buffer_end, Callback cb, Args&&... args) const
            noexcept;
    };

    using unique_directory = basic_directory<unique_handle>;
    using directory_ref    = basic_directory<handle_ref>;

} // namespace ntw::io

#include "../impl/directory.inl"
