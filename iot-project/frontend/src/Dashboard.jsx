import { useEffect, useState } from "react";

export default function Dashboard() {
  const [data, setData] = useState({
    temp: "--",
    humidity: "--",
    status: "Connecting...",
  });

  useEffect(() => {
    const ws = new WebSocket("ws://localhost:5000/");

    ws.onopen = () => {
      console.log("Frontend WebSocket connected");
      setData((prev) => ({ ...prev, status: "Connected" }));
    };

    ws.onmessage = (event) => {
      console.log("Frontend received:", event.data);

      try {
        const sensorData = JSON.parse(event.data);

        if (sensorData.temp !== undefined && sensorData.humidity !== undefined) {
          setData({
            temp: sensorData.temp,
            humidity: sensorData.humidity,
            status: "Live",
          });
        }
      } catch (error) {
        console.error("Invalid JSON:", event.data);
      }
    };

    ws.onerror = (error) => {
      console.error("Frontend WebSocket error:", error);
      setData((prev) => ({ ...prev, status: "Error" }));
    };

    ws.onclose = () => {
      console.log("Frontend WebSocket disconnected");
      setData((prev) => ({ ...prev, status: "Disconnected" }));
    };

    return () => ws.close();
  }, []);

  return (
    <div style={{ padding: "20px", textAlign: "center" }}>
      <h1>ESP32 IoT Dashboard</h1>

      <h3>Status: {data.status}</h3>

      <h2>Temperature: {data.temp} °C</h2>
      <h2>Humidity: {data.humidity} %</h2>
    </div>
  );
}