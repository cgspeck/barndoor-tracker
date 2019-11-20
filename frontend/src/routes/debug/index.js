import { h, Component } from 'preact';
import style from './style';

export default class Debug extends Component {
	state = {
		apSettings: {
			ssid: '',
			key: '',
		}
	}

	async componentDidMount() {
		this.getAllSettings().then(r => this.setState({...r}));
	}

	getAllMockSettings() {
		return({
			apSettings: {
				ssid: 'not set',
				key: 'not set'
			}
		})
	}

	async getAllSettings() {
		const response = await fetch('http://localhost:8882/settings?q=debug');
		return await response.json();
	}

	render({}, { apSettings }) {
		return(
			<div class={style.debug}>
				<h1>Debug</h1>
				<p>NODE_ENV: {JSON.stringify(process.env.NODE_ENV)}</p>
				<h2>AP Settings</h2>
				<p>SSID: {apSettings.ssid}</p>
				<p>Key: {apSettings.key}</p>
			</div>
		)
	}
};
