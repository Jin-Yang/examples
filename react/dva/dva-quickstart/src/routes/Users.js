import React, { Component, PropTypes } from 'react';

// 引入 connect 工具函数
import { connect } from 'dva';

// Users 的 Presentational Component
// 暂时都没实现
import UserList from '../components/Users/UserList';
import UserSearch from '../components/Users/UserSearch';
import UserModal from '../components/Users/UserModal';

// 引入对应的样式
// 可以暂时新建一个空的
import styles from './Users.less';

function Users({ location, dispatch, users }) {
	const {
		loading, list, total, current,
		currentItem, modalVisible, modalType
	} = users;

	const userSearchProps = {};
	const userListProps={
		dataSource: list,
		total,
		loading,
		current,
	};
//	const userListProps = {
//		total: 3,
//		current: 1,
//		loading: false,
//		dataSource: [ {
//			name: '张三',
//			age: 23,
//			address: '成都',
//		}, {
//			name: '李四',
//			age: 24,
//			address: '杭州',
//		}, {
//			name: '王五',
//			age: 25,
//			address: '上海',
//		}, ],
//	};
	const userModalProps = {};

	return (
		<div className={styles.normal}>
			{/* 用户筛选搜索框 */}
			<UserSearch {...userSearchProps} />
			{/* 用户信息展示列表 */}
			<UserList {...userListProps} />
			{/* 添加用户 & 修改用户弹出的浮层 */}
			<UserModal {...userModalProps} />
		</div>
	);
}

// Users.propTypes = {
// 	users: PropTypes.object,
// };


// 指定订阅数据，这里关联了 users
function mapStateToProps({ users }) {
	return {users};
}

// 建立数据关联关系
export default connect(mapStateToProps)(Users);
