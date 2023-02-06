#ifndef SECURE_SERVERLESS_MESSAGE_CLIENTKS_H_
#define SECURE_SERVERLESS_MESSAGE_CLIENTKS_H_

#include "request.h"

#include <string>

enum KeyServiceRequestType : int {
  USER_REGISTER,
  UPSERT_WORKER_KEY,
  UPSERT_MODEL_KEY,
  ADD_MODEL_ACCESS_WORKER,
  ADD_MODEL_ACCESS_USER
};

struct KeyServiceRequest : public Request {
  KeyServiceRequest(int request_type, const std::string& user_id,
    const std::string& payload) 
    : type_(request_type), user_id_(user_id), payload_(payload) {}
  ~KeyServiceRequest() = default;
  std::string EncodeTo() const override;

  int type_;
  std::string user_id_;
  std::string payload_;
};

extern KeyServiceRequest DecodeKeyServiceRequest(const std::string& request);

struct KeyServiceReply : public Reply {
  KeyServiceReply(bool success, const std::string& reply)
    : success_(success), reply_(reply) {}
  ~KeyServiceReply() = default;
  std::string EncodeTo() const override;
  bool success_; // fail if the proposed_id_ has been taken.
  std::string reply_;
};

extern KeyServiceReply DecodeKeyServiceReply(const std::string& reply);

struct UpsertWorkerKeyRequest : public Request {
  UpsertWorkerKeyRequest(const std::string& mrenclave,
    const std::string& decrypt_key) : mrenclave_(mrenclave),
    decrypt_key_(decrypt_key) {}
  ~UpsertWorkerKeyRequest() = default;
  std::string EncodeTo() const override;

  std::string mrenclave_;
  std::string decrypt_key_;
};

extern UpsertWorkerKeyRequest DecodeUpsertWorkerKeyRequest(
  const std::string& request);

struct UpsertModelKeyRequest : public Request {
  UpsertModelKeyRequest(const std::string& model_id,
    const std::string& decrypt_key) : model_id_(model_id),
    decrypt_key_(decrypt_key) {}
  ~UpsertModelKeyRequest() = default;
  std::string EncodeTo() const override;

  std::string model_id_;
  std::string decrypt_key_;
};

extern UpsertModelKeyRequest DecodeUpsertModelKeyRequest(
  const std::string& request);

struct AddModelAccessWorker : public Request {
  AddModelAccessWorker(const std::string& model_id,
    const std::string& mrenclave) : model_id_(model_id),
    mrenclave_(mrenclave) {}
  ~AddModelAccessWorker() = default;
  std::string EncodeTo() const override;

  std::string model_id_;
  std::string mrenclave_;
};

extern AddModelAccessWorker DecodeAddModelAccessWorker(
  const std::string& request);

struct AddModelAccessUser : public Request {
  AddModelAccessUser(const std::string& model_id,
    const std::string& user_id) : model_id_(model_id),
    user_id_(user_id) {}
  ~AddModelAccessUser() = default;
  std::string EncodeTo() const override;

  std::string model_id_;
  std::string user_id_;
};

extern AddModelAccessUser DecodeAddModelAccessUser(
  const std::string& request);

#endif  // SECURE_SERVERLESS_MESSAGE_CLIENTKS_H_
