/*!
 * @file frame_bypass.h
 * @date July/14/2023
 * @author eleven
 */

#pragma once

#include <memory>
#include <string>

#include "fastdds/dds/domain/DomainParticipant.hpp"
#include "fastdds/dds/publisher/DataWriter.hpp"
#include "fastdds/dds/publisher/DataWriterListener.hpp"
#include "fastdds/dds/publisher/Publisher.hpp"
#include "fastdds/dds/topic/TypeSupport.hpp"
#include "glog/logging.h"

#include "dds/fastdds_dynamic_pub.h"

#include "idl_interface/perception/frame_encoderPubSubTypes.h"

namespace krider {
namespace multiperception {

using krider::dds_common::FastDynamicPublisher;
using krider::perception::OneCameraFrame;
using krider::perception::OneCameraFramePubSubType;
using krider::sensors::Image;

template <typename _T, typename _Type> struct identity {
  typedef _T i_T;
  typedef _Type i_Type;
};

template <typename T = OneCameraFrame, typename Type = OneCameraFramePubSubType>
class FrameBypass {
public:
  FrameBypass(int idx, std::string FrameParticipant,
              std::string FramePublisher) {
    FrameBypassImpl(idx, FrameParticipant, FramePublisher,
                             identity<T, Type>());
  }
  bool BypassPub(std::shared_ptr<T> cur_data) {
    return BypassPubImpl(cur_data, identity<T, Type>());
  }

  void Stop() { publisher_ptr_->Stop(); }

private:
  template <typename _T, typename _Type>
  void FrameBypassImpl(int idx, std::string FrameParticipant,
                       std::string FramePublisher, identity<_T, _Type> idtt) {
    LOG(ERROR) << "FrameBypass: Unsupported Type";
  }

  void  FrameBypassImpl(int idx, std::string FrameParticipant,
                  std::string FramePublisher,
                  identity<OneCameraFrame, OneCameraFramePubSubType> idtt) {
    index_ = idx;
    publisher_ptr_.reset(
        new FastDynamicPublisher<T, Type>(FrameParticipant, FramePublisher));
    LOG(ERROR) << "FrameBypass Index: " << index_;
    Init();
  }

  template <typename U, typename V>
  bool BypassPubImpl(std::shared_ptr<U> cur_data, identity<U, V> idtt) {
    LOG(ERROR) << "FrameBypass: Unsupported Type";
  }

  bool BypassPubImpl(std::shared_ptr<T> cur_data,
                     identity<OneCameraFrame, OneCameraFramePubSubType> idtt) {
    if (publisher_ptr_->IsMatched()) {
      publisher_ptr_->PubMsg(cur_data);
    } else {
      LOG(ERROR) << "FrameBypass: publisher is not matched!";
    }
  }

  void Init() { publisher_ptr_->Run(); }

private:
  int index_;
  std::unique_ptr<FastDynamicPublisher<T, Type>> publisher_ptr_;
};

} // namespace multiperception
} // namespace krider
