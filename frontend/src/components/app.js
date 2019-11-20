import { h, Component } from 'preact';
import { Router } from 'preact-router';

import Header from './header';

// Code-splitting is automated for routes
import Debug from '../routes/debug';
import Home from '../routes/home';
import APSettings from '../routes/ap_settings';

export default class App extends Component {
	/** Gets fired when the route changes.
	 *	@param {Object} event		"change" event from [preact-router](http://git.io/preact-router)
	 *	@param {string} event.url	The newly routed URL
	 */
	handleRoute = e => {
		this.currentUrl = e.url;
	};

	render() {
		return (
			<div id="app">
				<Header />
				<Router onChange={this.handleRoute}>
					<Debug path="/debug" />
					<Home path="/" />
					<APSettings path="/ap_settings" />
				</Router>
			</div>
		);
	}
}
