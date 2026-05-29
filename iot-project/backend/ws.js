const WebSocket = require("ws");

let latestSensorData = null;

function setupWebSocket(server) {
  const wss = new WebSocket.Server({
    server,
    path: "/",
  });

  wss.on("connection", (ws) => {
    console.log("Client connected");

    if (latestSensorData) {
      ws.send(latestSensorData);
    }

    ws.on("message", (message) => {
      const data = message.toString();

      console.log("Received:", data);

      try {
        const parsed = JSON.parse(data);

        if (parsed.temp !== undefined && parsed.humidity !== undefined) {
          latestSensorData = data;
        }
      } catch (error) {
        console.log("Invalid JSON received:", data);
      }

      wss.clients.forEach((client) => {
        if (client.readyState === WebSocket.OPEN) {
          client.send(data);
        }
      });
    });

    ws.on("close", () => {
      console.log("Client disconnected");
    });

    ws.on("error", (error) => {
      console.error("WebSocket error:", error.message);
    });
  });

  console.log("WebSocket server ready");
}

module.exports = { setupWebSocket };