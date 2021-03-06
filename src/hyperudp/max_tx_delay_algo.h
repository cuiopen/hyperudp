/* Copyright (c) 2016-2017, Bin Wei <bin@vip.qq.com>
 * All rights reserved.
 * 
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions are
 * met:
 * 
 *     * Redistributions of source code must retain the above copyright
 * notice, this list of conditions and the following disclaimer.
 *     * Redistributions in binary form must reproduce the above
 * copyright notice, this list of conditions and the following disclaimer
 * in the documentation and/or other materials provided with the
 * distribution.
 *     * The names of its contributors may not be used to endorse or 
 * promote products derived from this software without specific prior 
 * written permission.
 * 
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS
 * "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT
 * LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR
 * A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT
 * OWNER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL,
 * SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT
 * LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE,
 * DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY
 * THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
 * (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
 * OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 */
#ifndef HUDP_MAX_TX_DELAY_ALGO_H_
#define HUDP_MAX_TX_DELAY_ALGO_H_

#include "hyperudp/tx_delay_algo.h"
#include "hyperudp/env.h"

namespace hudp {

class MaxTxDelayAlgo : public TxDelayAlgo {
 public:
  MaxTxDelayAlgo(const Env& env)
    : env_(env), max_delay_(env.opt().max_tx_delay) {}

  virtual Action OnPendingSeg(size_t seg_count) override {
    if (seg_count == 1) {
      // reset timer when first segment buffered
      return {kResetFlushTimer, static_cast<unsigned>(max_delay_)};
    } else {
      // if seg_count == 0, all flushed, so do nothing
      // if seg_count >= 2, timer has been set, just waiting
      return {kNoOp, 0};
    }
  }

 protected:
  const Env& env_;
  size_t max_delay_;
};

}  // namespace hudp

#endif  // HUDP_MAX_TX_DELAY_ALGO_H_
