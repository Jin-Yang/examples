import { hashHistory } from 'dva/router';

import { query } from '../services/users';
// // 处理异步请求
// import request from '../utils/request';
// import qs from 'qs';
// async function query(params) {
// 	return request(`/api/users?${qs.stringify(params)}`);
// }

export default {
	namespace: 'users',

	state: {
		list: [],
		total: null,
		loading: false, // 控制加载状态
		current: null, // 当前分页信息
		currentItem: {}, // 当前操作的用户对象
		modalVisible: false, // 弹出窗的显示状态
		modalType: 'create', // 弹出窗的类型（添加用户，编辑用户）
	},

	// Quick Start 已经介绍过 subscriptions 的概念，这里不在多说
	subscriptions: {
		setup({ dispatch, history }) {
			history.listen(location => {
				if (location.pathname === '/users') {
					dispatch({
						type: 'querySuccess',
						payload: {}
					});
				}
			});
		},
	},

	effects: {
		*query({ payload }, { select, call, put }) {
			yield put({ type: 'showLoading' });
			const { data } = yield call(query);
			if (data) {
				yield put({
					type: 'querySuccess',
					payload: {
						list: data.data,
						total: data.page.total,
						current: data.page.current
					}
				});
			}
		},

		*create(){},
		*'delete'(){},
		*update(){},
	},
	reducers: {
		showLoading(state, action){
			return { ...state, loading: true };
		}, // 控制加载状态的 reducer
		// showLoading(){},
		showModal(){},  // 控制 Modal 显示状态的 reducer
		hideModal(){},
		// 使用服务器数据返回
		querySuccess(state, action){
			return {...state, ...action.payload, loading: false};
		},
//		querySuccess(state){
//			const mock = {
//				total: 3,
//				current: 1,
//				loading: false,
//				list: [ {
//					id: 1,
//					name: '张三',
//					age: 23,
//					address: '成都',
//				}, {
//					id: 2,
//					name: '李四',
//					age: 24,
//					address: '杭州',
//				}, {
//					id: 3,
//					name: '王五',
//					age: 25,
//					address: '上海',
//				}, ],
//
//			};
//			return {...state, ...mock, loading: false};
//		},
		createSuccess(){},
		deleteSuccess(){},
		updateSuccess(){},
	}
}

