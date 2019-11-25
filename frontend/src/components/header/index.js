import { h, Component } from 'preact';
import { route } from 'preact-router';
import TopAppBar from 'preact-material-components/TopAppBar';
import Drawer from 'preact-material-components/Drawer';
import 'preact-material-components/Drawer/style.css';
import 'preact-material-components/Dialog/style.css';
import 'preact-material-components/List/style.css';
import 'preact-material-components/TopAppBar/style.css';

export default class Header extends Component {
	closeDrawer() {
		this.drawer.MDComponent.open = false;
	}

	openDrawer = () => (this.drawer.MDComponent.open = true);

	drawerRef = drawer => (this.drawer = drawer);

	debugLink = (selectedRoute, goDebug) => {
		if (process.env.NODE_ENV === 'development') {
			return (
				<Drawer.DrawerItem selected={selectedRoute == '/debug'} onClick={goDebug}>
					Debug
				</Drawer.DrawerItem>
			)
		}
	}

	linkTo = path => () => {
		route(path);
		this.closeDrawer();
	};

	goAPSettings = this.linkTo('/ap_settings');
	goDebug = this.linkTo('/debug');
	goHome = this.linkTo('/');

	render({selectedRoute}, {}) {
		return (
			<div>
				<TopAppBar className="topappbar">
					<TopAppBar.Row>
						<TopAppBar.Section align-start>
							<TopAppBar.Icon menu onClick={this.openDrawer}>
								menu
							</TopAppBar.Icon>
							<TopAppBar.Title>Barndoor Tracker</TopAppBar.Title>
						</TopAppBar.Section>
					</TopAppBar.Row>
				</TopAppBar>

				<Drawer modal ref={this.drawerRef}>
					<Drawer.DrawerContent>
						<Drawer.DrawerItem selected={selectedRoute == '/'} onClick={this.goHome}>
							{/*<List.ItemGraphic>home</List.ItemGraphic> */}
							Home
						</Drawer.DrawerItem>

						<Drawer.DrawerItem selected={selectedRoute == '/ap_settings'} onClick={this.goAPSettings}>
							AP Settings
						</Drawer.DrawerItem>
						{
							this.debugLink(selectedRoute, this.goDebug)
						}
					</Drawer.DrawerContent>
				</Drawer>
			</div>
		)
	}
}
