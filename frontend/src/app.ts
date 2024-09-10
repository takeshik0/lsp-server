// src/app.ts
const socket = new WebSocket("ws://localhost:8080"); // WebSocket connection to the backend

socket.onopen = () => {
  console.log("Connection opened");
  const lspRequest = {
    jsonrpc: "2.0",
    id: 1,
    method: "textDocument/hover",
    params: { textDocument: { uri: "file:///example.cpp" }, position: { line: 10, character: 15 } }
  };
  socket.send(JSON.stringify(lspRequest)); // Send request to backend
};

socket.onmessage = (event) => {
  const response = JSON.parse(event.data);
  console.log("Response from server: ", response);
  displayResult(response);
};

socket.onerror = (error) => {
  console.error("WebSocket Error: ", error);
};

socket.onclose = () => {
  console.log("Connection closed");
};

function displayResult(response: any) {
  const outputElement = document.getElementById("output");
  if (outputElement && response.result && response.result.contents) {
    outputElement.innerHTML = `<pre>${JSON.stringify(response.result.contents, null, 2)}</pre>`;
  }
}
