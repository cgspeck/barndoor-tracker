import { h, Component } from 'preact';
import style from './style';
import { getAPSettings } from '../../lib/settings';

export default class APSettings extends Component {
	state = {
		apSettings: {
			ssid: null,
			key: null
		},
		error: null,
		info: null,
	};

	async componentDidMount() {
		getAPSettings()
			.then(r => this.setState({ apSettings: {...r} }))
			.catch(e => {
				console.error('problem', e)
				this.setState({error: e});
			});
	}

	errorToast() {
		if (this.state.error != null) {
			return(
				<p>
					{ this.state.error.toString() }
				</p>
			)
		}
	}

	render({}, { apSettings }) {
		return(
			<div class={style.ap}>
				<h1>Access Point Settings</h1>
				{this.errorToast()}
				<h2>AP Settings</h2>
				<p>SSID: {apSettings.ssid}</p>
				<p>Key: {apSettings.key}</p>
			</div>
		)
	}
};
