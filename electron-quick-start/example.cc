#include <nan.h>

const int maxValue = 10;
int numberOfCalls = 0;

// NAN_METHOD(WhoAmI) {
//   auto message = Nan::New<v8::String>("I'm a Node Hero!").ToLocalChecked();
//   info.GetReturnValue().Set(message);
// }

// NAN_METHOD(Increment) {
//   if (!info[0]->IsNumber()) {
//     Nan::ThrowError("Argument must be a number");
//     return;
//   }

//   double infoValue = info[0]->NumberValue(Nan::GetCurrentContext()).FromJust();
//   if (numberOfCalls + infoValue > maxValue) {
//     Nan::ThrowError("Counter went through the roof!");
//     return;
//   }

//   numberOfCalls += infoValue;

//   auto currentNumberOfCalls =
//     Nan::New<v8::Number>(numberOfCalls);

//   info.GetReturnValue().Set(currentNumberOfCalls);
// }
NAN_METHOD(Start) {
    StartUpOBS(); // calls into MyLibobs StartUpOBS()
}

NAN_METHOD(Stop) {
    ShutDown(); // calls into MyLibobs ShutDown()
}


NAN_MODULE_INIT(Initialize) {
  NAN_EXPORT(target, Start);
  NAN_EXPORT(target, Stop);
}

NODE_MODULE(addon, Initialize)