const express = require("express");
const http = require("http");
const cors = require("cors");
require("dotenv").config();

const { setupWebSocket } = require("./ws");

const app = express();

app.use(cors());
app.use(express.json());

app.get("/", (req, res) => {
  res.send("IoT Backend Running");
});

const server = http.createServer(app);

setupWebSocket(server);

const PORT = process.env.PORT || 5000;

server.listen(PORT, "0.0.0.0", () => {
  console.log(`HTTP server running on port ${PORT}`);
  console.log(`WebSocket server running at ws://localhost:${PORT}/`);
});