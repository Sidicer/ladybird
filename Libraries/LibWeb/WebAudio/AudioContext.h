/*
 * Copyright (c) 2023, Luke Wilde <lukew@serenityos.org>
 *
 * SPDX-License-Identifier: BSD-2-Clause
 */

#pragma once

#include <LibWeb/Bindings/AudioContextPrototype.h>
#include <LibWeb/HighResolutionTime/DOMHighResTimeStamp.h>
#include <LibWeb/WebAudio/BaseAudioContext.h>
#include <LibWeb/WebAudio/MediaElementAudioSourceNode.h>

namespace Web::WebAudio {

struct AudioContextOptions {
    Bindings::AudioContextLatencyCategory latency_hint = Bindings::AudioContextLatencyCategory::Interactive;
    Optional<float> sample_rate;
};

struct AudioTimestamp {
    double context_time { 0 };
    double performance_time { 0 };
};

// https://webaudio.github.io/web-audio-api/#AudioContext
class AudioContext final : public BaseAudioContext {
    WEB_PLATFORM_OBJECT(AudioContext, BaseAudioContext);
    GC_DECLARE_ALLOCATOR(AudioContext);

public:
    static WebIDL::ExceptionOr<GC::Ref<AudioContext>> construct_impl(JS::Realm&, Optional<AudioContextOptions> const& context_options = {});

    virtual ~AudioContext() override;

    double base_latency() const { return m_base_latency; }
    double output_latency() const { return m_output_latency; }
    AudioTimestamp get_output_timestamp();
    WebIDL::ExceptionOr<GC::Ref<WebIDL::Promise>> resume();
    WebIDL::ExceptionOr<GC::Ref<WebIDL::Promise>> suspend();
    WebIDL::ExceptionOr<GC::Ref<WebIDL::Promise>> close();

    WebIDL::ExceptionOr<GC::Ref<MediaElementAudioSourceNode>> create_media_element_source(GC::Ptr<HTML::HTMLMediaElement>);

private:
    explicit AudioContext(JS::Realm& realm)
        : BaseAudioContext(realm)
    {
    }

    virtual void initialize(JS::Realm&) override;
    virtual void visit_edges(Cell::Visitor&) override;

    double m_base_latency { 0 };
    double m_output_latency { 0 };

    bool m_allowed_to_start = true;
    Vector<GC::Ref<WebIDL::Promise>> m_pending_resume_promises;
    bool m_suspended_by_user = false;

    bool start_rendering_audio_graph();
};

}
