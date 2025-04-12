#--建表
CREATE TABLE `user` (
    `user_id` bigint NOT NULL DEFAULT '-1' COMMENT '用户id',
    `nick_name` varchar(35) CHARACTER SET utf8mb3 COLLATE utf8mb3_bin DEFAULT NULL COMMENT '昵称',
    `avatar` varchar(255) CHARACTER SET utf8mb3 COLLATE utf8mb3_bin DEFAULT NULL COMMENT '头像',
    `true_name` varchar(20) CHARACTER SET utf8mb3 COLLATE utf8mb3_bin DEFAULT NULL COMMENT '真实姓名',
    `sex` tinyint(1) DEFAULT NULL COMMENT '性别 0男，1女',
    `create_time` datetime DEFAULT CURRENT_TIMESTAMP,
    `update_time` datetime DEFAULT CURRENT_TIMESTAMP ON UPDATE CURRENT_TIMESTAMP,
    PRIMARY KEY (`user_id`)
) ENGINE=InnoDB COMMENT='用户基础信息表';
#--插入测试用户
INSERT INTO tllive.t_user (user_id, nick_name, avatar, true_name, sex, create_time, update_time) VALUES (1, 'roy', '/img/avatar.png', 'test', 1, '2025-04-10 17:35:12', '2024-05-10 17:35:15');



CREATE TABLE `sms` (
     `id` bigint unsigned NOT NULL AUTO_INCREMENT COMMENT '主键id',
     `code` int unsigned DEFAULT '0' COMMENT '验证码',
     `phone` varchar(200) CHARACTER SET utf8mb4 COLLATE utf8mb4_0900_ai_ci DEFAULT '' COMMENT '手机号',
     `send_time` datetime DEFAULT CURRENT_TIMESTAMP COMMENT '发送时间',
     `update_time` datetime DEFAULT CURRENT_TIMESTAMP ON UPDATE CURRENT_TIMESTAMP COMMENT '更新时间',
     PRIMARY KEY (`id`),
     KEY `code` (`code`)
) ENGINE=InnoDB AUTO_INCREMENT=1 COMMENT='短信发送记录';


CREATE TABLE `user_phone` (
                                `id` bigint unsigned NOT NULL AUTO_INCREMENT COMMENT '主键id',
                                `phone` varchar(200) CHARACTER SET utf8mb3 COLLATE utf8mb3_bin NOT NULL DEFAULT '' COMMENT '手机号',
                                `user_id` bigint DEFAULT '-1' COMMENT '用户id',
                                `status` tinyint DEFAULT '-1' COMMENT '状态(0无效，1有效)',
                                `create_time` datetime DEFAULT CURRENT_TIMESTAMP COMMENT '创建时间',
                                `update_time` datetime DEFAULT CURRENT_TIMESTAMP ON UPDATE CURRENT_TIMESTAMP COMMENT '更新时间',
                                PRIMARY KEY (`id`),
                                UNIQUE KEY `udx_phone` (`phone`),
                                KEY `idx_user_id` (`user_id`)
) ENGINE=InnoDB AUTO_INCREMENT=1 COMMENT='用户手机表';




create table if not exists cosid_machine
(
    name            varchar(100)     not null comment '{namespace}.{machine_id}',
    namespace       varchar(100)     not null,
    machine_id      integer unsigned not null default 0,
    last_timestamp  bigint unsigned  not null default 0,
    instance_id     varchar(100)     not null default '',
    distribute_time bigint unsigned  not null default 0,
    revert_time     bigint unsigned  not null default 0,
    constraint cosid_machine_pk
    primary key (name)
    ) engine = InnoDB;

create index idx_namespace on cosid_machine (namespace);
create index idx_instance_id on cosid_machine (instance_id);