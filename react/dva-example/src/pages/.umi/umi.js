import React from 'react';
import ReactDOM from 'react-dom';
import createHistory from 'umi/_createHistory';
import FastClick from 'umi-fastclick';


document.addEventListener(
  'DOMContentLoaded',
  () => {
    FastClick.attach(document.body);
  },
  false,
);

// create history
window.g_history = createHistory({
  basename: window.routerBase,
});


// render
function render() {
  const DvaContainer = require('./DvaContainer').default;
ReactDOM.render(React.createElement(
  DvaContainer,
  null,
  React.createElement(require('./router').default)
), document.getElementById('root'));
}
render();

// hot module replacement
if (module.hot) {
  module.hot.accept('./router', () => {
    render();
  });
}

require('/home/andy/Workspace/0-examples/react/dva-example/src/global.css');
// Enable service worker
if (process.env.NODE_ENV === 'production') {
  require('./registerServiceWorker');
}
      