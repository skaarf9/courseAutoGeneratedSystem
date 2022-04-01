/*
 Navicat Premium Data Transfer

 Source Server         : MySQL
 Source Server Type    : MySQL
 Source Server Version : 80028
 Source Host           : localhost:3306
 Source Schema         : school

 Target Server Type    : MySQL
 Target Server Version : 80028
 File Encoding         : 65001

 Date: 01/04/2022 22:32:10
*/

SET NAMES utf8mb4;
SET FOREIGN_KEY_CHECKS = 0;

-- ----------------------------
-- Table structure for s_class
-- ----------------------------
DROP TABLE IF EXISTS `s_class`;
CREATE TABLE `s_class`  (
  `s_id` int(0) UNSIGNED NOT NULL AUTO_INCREMENT COMMENT '班级id',
  `s_name` char(15) CHARACTER SET utf8mb4 COLLATE utf8mb4_0900_ai_ci NOT NULL COMMENT '班级名称',
  PRIMARY KEY (`s_id`) USING BTREE
) ENGINE = InnoDB AUTO_INCREMENT = 11 CHARACTER SET = utf8mb4 COLLATE = utf8mb4_0900_ai_ci ROW_FORMAT = Dynamic;

-- ----------------------------
-- Records of s_class
-- ----------------------------
INSERT INTO `s_class` VALUES (1, '一年级一班');
INSERT INTO `s_class` VALUES (2, '一年级二班');
INSERT INTO `s_class` VALUES (3, '一年级三班');
INSERT INTO `s_class` VALUES (4, '一年级四班');
INSERT INTO `s_class` VALUES (5, '一年级五班');
INSERT INTO `s_class` VALUES (6, '一年级六班');
INSERT INTO `s_class` VALUES (7, '一年级七班');
INSERT INTO `s_class` VALUES (8, '一年级八班');
INSERT INTO `s_class` VALUES (11, '一年级九班');
INSERT INTO `s_class` VALUES (12, '一年级十班');

-- ----------------------------
-- Table structure for s_classroom
-- ----------------------------
DROP TABLE IF EXISTS `s_classroom`;
CREATE TABLE `s_classroom`  (
  `s_id` int(0) UNSIGNED NOT NULL AUTO_INCREMENT COMMENT '教室id',
  `s_name` varchar(255) CHARACTER SET utf8mb4 COLLATE utf8mb4_0900_ai_ci NOT NULL COMMENT '教室名称',
  `s_capacity` tinyint(0) UNSIGNED NOT NULL COMMENT '教室大小',
  PRIMARY KEY (`s_id`) USING BTREE
) ENGINE = InnoDB AUTO_INCREMENT = 25 CHARACTER SET = utf8mb4 COLLATE = utf8mb4_0900_ai_ci ROW_FORMAT = Dynamic;

-- ----------------------------
-- Records of s_classroom
-- ----------------------------
INSERT INTO `s_classroom` VALUES (1, '1101', 2);
INSERT INTO `s_classroom` VALUES (2, '1102', 2);
INSERT INTO `s_classroom` VALUES (3, '1103', 2);
INSERT INTO `s_classroom` VALUES (4, '1104', 4);
INSERT INTO `s_classroom` VALUES (5, '1201', 2);
INSERT INTO `s_classroom` VALUES (25, '1202', 4);
INSERT INTO `s_classroom` VALUES (26, '1203', 4);
INSERT INTO `s_classroom` VALUES (27, '1204', 2);
INSERT INTO `s_classroom` VALUES (28, '1301', 4);

-- ----------------------------
-- Table structure for s_subject
-- ----------------------------
DROP TABLE IF EXISTS `s_subject`;
CREATE TABLE `s_subject`  (
  `s_id` int(0) UNSIGNED NOT NULL AUTO_INCREMENT COMMENT '学科id',
  `s_name` varchar(32) CHARACTER SET utf8mb4 COLLATE utf8mb4_0900_ai_ci NOT NULL COMMENT '学科名称',
  `s_workload` tinyint(0) UNSIGNED NOT NULL COMMENT '学科工作量(单位班)',
  `s_duration` int(0) UNSIGNED NOT NULL COMMENT '学科总课时',
  `s_weeklyLessonNum` tinyint(0) UNSIGNED NOT NULL COMMENT '每周课时',
  PRIMARY KEY (`s_id`) USING BTREE
) ENGINE = InnoDB AUTO_INCREMENT = 14 CHARACTER SET = utf8mb4 COLLATE = utf8mb4_0900_ai_ci ROW_FORMAT = Dynamic;

-- ----------------------------
-- Records of s_subject
-- ----------------------------
INSERT INTO `s_subject` VALUES (1, '语文', 2, 30, 4);
INSERT INTO `s_subject` VALUES (2, '数学', 2, 30, 4);
INSERT INTO `s_subject` VALUES (3, '英语', 2, 30, 4);
INSERT INTO `s_subject` VALUES (4, '物理', 2, 16, 3);
INSERT INTO `s_subject` VALUES (5, '化学', 4, 21, 3);
INSERT INTO `s_subject` VALUES (6, '历史', 4, 15, 2);
INSERT INTO `s_subject` VALUES (7, '生物', 4, 17, 3);
INSERT INTO `s_subject` VALUES (8, '地理', 3, 20, 3);
INSERT INTO `s_subject` VALUES (9, '政治', 3, 24, 2);
INSERT INTO `s_subject` VALUES (10, '体育', 3, 20, 4);
INSERT INTO `s_subject` VALUES (14, '文艺', 3, 20, 2);

-- ----------------------------
-- Table structure for s_teacher
-- ----------------------------
DROP TABLE IF EXISTS `s_teacher`;
CREATE TABLE `s_teacher`  (
  `s_id` int(0) UNSIGNED NOT NULL AUTO_INCREMENT COMMENT '教师id',
  `s_name` varchar(255) CHARACTER SET utf8mb4 COLLATE utf8mb4_0900_ai_ci NOT NULL COMMENT '教师名称',
  `s_workload` tinyint(0) UNSIGNED NOT NULL COMMENT '教师工作量(单位course)',
  `s_subject_suitable_index` varchar(255) CHARACTER SET utf8mb4 COLLATE utf8mb4_0900_ai_ci NOT NULL COMMENT '教师的学科合适程度(是一个组数据形成的字符串)',
  PRIMARY KEY (`s_id`) USING BTREE
) ENGINE = InnoDB AUTO_INCREMENT = 12 CHARACTER SET = utf8mb4 COLLATE = utf8mb4_0900_ai_ci ROW_FORMAT = Dynamic;

-- ----------------------------
-- Records of s_teacher
-- ----------------------------
INSERT INTO `s_teacher` VALUES (1, '张三', 5, '1,6,8,7,4,9,1,3,9,9,3');
INSERT INTO `s_teacher` VALUES (2, '李四', 5, '7,4,10,1,9,6,10,5,2,8,6');
INSERT INTO `s_teacher` VALUES (3, '王五', 5, '3,7,8,3,6,1,1,7,10,9,10');
INSERT INTO `s_teacher` VALUES (4, '周润发', 5, '4,8,3,10,4,8,10,0,1,2,6');
INSERT INTO `s_teacher` VALUES (5, '谢婧婷', 5, '4,1,10,9,0,8,0,3,10,4,5');
INSERT INTO `s_teacher` VALUES (6, '郑和', 5, '1,6,4,6,0,9,5,6,1,7,8');
INSERT INTO `s_teacher` VALUES (7, '杨和宇', 5, '5,6,10,1,5,0,6,5,5,10,4');
INSERT INTO `s_teacher` VALUES (8, '哈根听', 5, '3,5,5,9,5,4,1,0,10,3,7');
INSERT INTO `s_teacher` VALUES (17, '3B1B', 5, '9,10,3,6,2,7,9,2,1,0,2');
INSERT INTO `s_teacher` VALUES (18, '刘德华', 5, '9,7,2,5,6,2,4,6,7,2,8');

SET FOREIGN_KEY_CHECKS = 1;
