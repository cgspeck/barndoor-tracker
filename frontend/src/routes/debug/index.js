import { h, Component } from 'preact';
import style from './style';
import { getAllSettings } from '../../lib/settings';

export default class Debug extends Component {
	state = {
		"apSettings": {
			"ssid": null,
			"key": null
		},
		"debug": {
			"currentMillis": null
		},
		"location": {
			"latitude": null,
			"magDeclination": null,
			"x_offset": null,
			"y_offset": null,
			"z_offset": null
		}
	}

	async componentDidMount() {
		getAllSettings().then(r => {
			console.log('got response', r);
			this.setState({...r})
		});
	}

	render({}, { apSettings, debug, location }) {
		return(
			<div class={style.debug}>
				<h1>Debug</h1>
				<p>NODE_ENV: {JSON.stringify(process.env.NODE_ENV)}</p>
				<p>currentMillis: {debug.currentMillis}</p>
				<h2>AP Settings</h2>
				<p>SSID: {apSettings.ssid}</p>
				<p>Key: {apSettings.key}</p>
				<h2>Location Settings</h2>
				<p>Latitude: {location.latitude}</p>
				<p>magDeclination: {location.magDeclination}</p>
				<p>x_offset: {location.x_offset}</p>
				<p>y_offset: {location.y_offset}</p>
				<p>z_offset: {location.z_offset}</p>
			</div>
		)
	}
};
