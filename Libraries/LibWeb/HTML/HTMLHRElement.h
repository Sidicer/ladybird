/*
 * Copyright (c) 2018-2020, Andreas Kling <andreas@ladybird.org>
 *
 * SPDX-License-Identifier: BSD-2-Clause
 */

#pragma once

#include <LibWeb/ARIA/Roles.h>
#include <LibWeb/HTML/HTMLElement.h>

namespace Web::HTML {

class HTMLHRElement final : public HTMLElement {
    WEB_PLATFORM_OBJECT(HTMLHRElement, HTMLElement);
    GC_DECLARE_ALLOCATOR(HTMLHRElement);

public:
    virtual ~HTMLHRElement() override;

    // https://www.w3.org/TR/html-aria/#el-hr
    virtual Optional<ARIA::Role> default_role() const override { return ARIA::Role::separator; }

private:
    HTMLHRElement(DOM::Document&, DOM::QualifiedName);

    virtual void initialize(JS::Realm&) override;

    virtual bool is_presentational_hint(FlyString const&) const override;
    virtual void apply_presentational_hints(GC::Ref<CSS::CascadedProperties>) const override;
};

}
