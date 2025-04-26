from enum import Enum
from fastapi import FastAPI, HTTPException
from fastapi.staticfiles import StaticFiles
from pydantic import BaseModel
from typing import List
from fastapi.middleware.cors import CORSMiddleware


class DeviceType(str, Enum):
    input = "input"
    output = "output"


class DeviceModel(BaseModel):
    id: int
    name: str
    type: DeviceType
    value: int | None = None


class DeviceValueModel(BaseModel):
    value: int


app = FastAPI()
app.devices = [
    DeviceModel(id=0, name="alcohol", type=DeviceType.input),
    DeviceModel(id=2, name="ledGreen", type=DeviceType.output),
    DeviceModel(id=3, name="ledYellow", type=DeviceType.output),
    DeviceModel(id=1, name="ledRed", type=DeviceType.output),

    DeviceModel(id=4, name="smoke", type=DeviceType.input),
    DeviceModel(id=5, name="ledOne", type=DeviceType.output),
    DeviceModel(id=6, name="ledTwo", type=DeviceType.output),
    DeviceModel(id=7, name="ledThree", type=DeviceType.output),
]

app.add_middleware(
    CORSMiddleware,
    allow_origins=["http://localhost:8080", "http://localhost:5173"],
    allow_credentials=True,
    allow_methods=["*"],
    allow_headers=["*"],
)


def setAlcoholLedsBasedOnAlcoholValue(alcoholValue):
    redLed = next((device for device in app.devices if device.name == "ledRed"), None)
    yellowLed = next((device for device in app.devices if device.name == "ledYellow"), None)
    greenLed = next((device for device in app.devices if device.name == "ledGreen"), None)

    redLed.value = 0
    yellowLed.value = 0
    greenLed.value = 0

    if alcoholValue <= 200:
        greenLed.value = 1
    elif alcoholValue > 200 and alcoholValue <= 250:
        yellowLed.value = 1
    else:
        redLed.value = 1

def setSmokeLedBasedOnGasValue(GasValue):
    blueLed = next((device for device in app.devices if device.name == "ledOne"), None)
    yellow2Led = next((device for device in app.devices if device.name == "ledTwo"), None)
    coolLed = next((device for device in app.devices if device.name == "ledThree"), None)

    blueLed.value = 0
    yellow2Led.value = 0
    coolLed.value = 0

    if GasValue <= 600:
        blueLed.value = 1
    elif GasValue > 600 and GasValue <= 700:
        yellow2Led.value = 1
    else:
        coolLed.value = 1


@app.get("/system_state")
async def get_system_state() -> List[DeviceModel]:
    return app.devices


@app.post("/devices/{device_name}")
async def set_device_value(device_name: str, valueModel: DeviceValueModel) -> dict:
    print(valueModel)
    model = next((device for device in app.devices if device.name == device_name), None)
    if model is None:
        raise HTTPException(status_code=404, detail="")
    model.value = valueModel.value

    if model.name == "alcohol":
        setAlcoholLedsBasedOnAlcoholValue(valueModel.value)
    if model.name == "smoke":
        setSmokeLedBasedOnGasValue(valueModel.value)

    return {"success": True}


app.mount('/', StaticFiles(directory='../frontend/dist', html=True))