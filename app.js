var WebSocketConnector = React.createClass({
  onplay: function () {
    websocket = new WebSocket(wsUri);
    websocket.onopen = function (evt) {
      console.log("Websocket:opened.");
    };
    websocket.onclose = function (evt) {
      console.log("Websocket:closed.");
    };
    websocket.onmessage = function (evt) {
      console.log("Websocket:message: " + evt);
    };
    websocket.onerror = function (evt) {
      console.log("Websocket:error: " + evt);
    };
  },

  onclose: function() {
    websocket.close();
  },

  getInitialState: function () {
    return {data: []};
  },

  render: function () {
    return (
      <div>
        <button class="play" onclick="this.onplay()">&#9654;</button>
        <button class="stop hidden" onclick="this.onstop()">&#9726;</button>
        <OSMFStream {...this.props} />
      </div>
    );
  }
});

var ListDNSItemWrapper = React.createClass({
  render: function() {
    return (
      <div>
        <DNSItem {...this.props} />
      </div>
    );
  }
});

var DNSItem = React.createClass({
  render: function() {

    var listItems = this.props.data.map(function(item) {
      return <li>{item}</li>;
    });
    return (
      <div>
        {...this.props.data}
      </div>
    );
  }
});


// Bubbles anyone ?
// http://superrb.com/blog/2013/06/14/bubbles-bubbles-everywhere