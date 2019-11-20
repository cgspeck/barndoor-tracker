import { h, Component } from 'preact';
import style from './style';
import { getAllSettings } from '../../lib/settings';

export default class Debug extends Component {
	state = {
		apSettings: {
			ssid: '',
			key: '',
		}
	}

	async componentDidMount() {
		getAllSettings().then(r => this.setState({...r}));
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
