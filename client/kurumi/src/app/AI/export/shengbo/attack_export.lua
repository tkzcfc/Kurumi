return {
    ["title"] = "new Tree",
    ["nodes"] = {
        [1] = {
            ["func"] = "",
            ["children"] = {
                [1] = {
                    ["children"] = {
                        [1] = {
                            ["type"] = "Action",
                            ["name"] = "Action_1",
                            ["func"] = "setBlackboard",
                            ["arg"] = {
                                [1] = "runAttactFail",
                                [2] = false,
                            },
                        },
                        [2] = {
                            ["children"] = {
                                [1] = {
                                    ["children"] = {
                                        [1] = {
                                            ["children"] = {
                                                [1] = {
                                                    ["children"] = {
                                                        [1] = {
                                                            ["type"] = "Action",
                                                            ["name"] = "Action_1",
                                                            ["func"] = "ai_do_handle",
                                                            ["arg"] = {
                                                                [1] = "CMD_Attack1",
                                                            },
                                                        },
                                                        [2] = {
                                                            ["type"] = "Action",
                                                            ["name"] = "Action_10",
                                                            ["func"] = "ai_reset_atk_interval",
                                                            ["arg"] = {
                                                                [1] = 1,
                                                            },
                                                        },
                                                    },
                                                    ["type"] = "Sequence",
                                                    ["name"] = "Sequence_1",
                                                    ["func"] = "",
                                                    ["arg"] = {
                                                    },
                                                },
                                                [2] = {
                                                    ["children"] = {
                                                        [1] = {
                                                            ["type"] = "Action",
                                                            ["name"] = "Action_2",
                                                            ["func"] = "ai_do_handle",
                                                            ["arg"] = {
                                                                [1] = "CMD_Attack2",
                                                            },
                                                        },
                                                        [2] = {
                                                            ["type"] = "Action",
                                                            ["name"] = "Action_10",
                                                            ["func"] = "ai_reset_atk_interval",
                                                            ["arg"] = {
                                                                [1] = 1,
                                                            },
                                                        },
                                                    },
                                                    ["type"] = "Sequence",
                                                    ["name"] = "Sequence_2",
                                                    ["func"] = "",
                                                    ["arg"] = {
                                                    },
                                                },
                                                [4] = {
                                                    ["children"] = {
                                                        [1] = {
                                                            ["type"] = "Action",
                                                            ["name"] = "Action_10",
                                                            ["func"] = "ai_reset_atk_interval",
                                                            ["arg"] = {
                                                                [1] = 0.5,
                                                            },
                                                        },
                                                        [2] = {
                                                            ["type"] = "Action",
                                                            ["name"] = "return true",
                                                            ["func"] = "setBlackboard",
                                                            ["arg"] = {
                                                                [1] = "runAttactFail",
                                                                [2] = true,
                                                            },
                                                        },
                                                    },
                                                    ["type"] = "Sequence",
                                                    ["name"] = "Sequence_10",
                                                    ["func"] = "",
                                                    ["arg"] = {
                                                    },
                                                },
                                                [3] = {
                                                    ["children"] = {
                                                        [1] = {
                                                            ["type"] = "Action",
                                                            ["name"] = "Action_3",
                                                            ["func"] = "ai_do_handle",
                                                            ["arg"] = {
                                                                [1] = "CMD_Skill",
                                                            },
                                                        },
                                                        [2] = {
                                                            ["type"] = "Action",
                                                            ["name"] = "Action_10",
                                                            ["func"] = "ai_reset_atk_interval",
                                                            ["arg"] = {
                                                                [1] = 1.5,
                                                            },
                                                        },
                                                    },
                                                    ["type"] = "Sequence",
                                                    ["name"] = "Sequence_3",
                                                    ["func"] = "",
                                                    ["arg"] = {
                                                    },
                                                },
                                            },
                                            ["type"] = "RandomSelector",
                                            ["name"] = "RandomSelector_1",
                                            ["func"] = "",
                                            ["arg"] = {
                                                [1] = 1,
                                                [2] = 1,
                                                [3] = 3,
                                                [4] = 10,
                                            },
                                        },
                                    },
                                    ["type"] = "Filter",
                                    ["name"] = "Filter_1",
                                    ["func"] = "ai_is_dis_too_long",
                                    ["arg"] = {
                                        [1] = 600,
                                    },
                                },
                                [2] = {
                                    ["children"] = {
                                        [1] = {
                                            ["children"] = {
                                                [1] = {
                                                    ["children"] = {
                                                        [1] = {
                                                            ["children"] = {
                                                                [1] = {
                                                                    ["type"] = "Action",
                                                                    ["name"] = "Action_1",
                                                                    ["func"] = "ai_do_handle",
                                                                    ["arg"] = {
                                                                        [1] = "CMD_Attack1",
                                                                    },
                                                                },
                                                                [2] = {
                                                                    ["type"] = "Action",
                                                                    ["name"] = "Action_10",
                                                                    ["func"] = "ai_reset_atk_interval",
                                                                    ["arg"] = {
                                                                        [1] = 1,
                                                                    },
                                                                },
                                                            },
                                                            ["type"] = "Sequence",
                                                            ["name"] = "Sequence_1",
                                                            ["func"] = "",
                                                            ["arg"] = {
                                                            },
                                                        },
                                                        [2] = {
                                                            ["children"] = {
                                                                [1] = {
                                                                    ["type"] = "Action",
                                                                    ["name"] = "Action_2",
                                                                    ["func"] = "ai_do_handle",
                                                                    ["arg"] = {
                                                                        [1] = "CMD_Attack2",
                                                                    },
                                                                },
                                                                [2] = {
                                                                    ["type"] = "Action",
                                                                    ["name"] = "Action_10",
                                                                    ["func"] = "ai_reset_atk_interval",
                                                                    ["arg"] = {
                                                                        [1] = 1,
                                                                    },
                                                                },
                                                            },
                                                            ["type"] = "Sequence",
                                                            ["name"] = "Sequence_2",
                                                            ["func"] = "",
                                                            ["arg"] = {
                                                            },
                                                        },
                                                        [4] = {
                                                            ["children"] = {
                                                                [1] = {
                                                                    ["type"] = "Action",
                                                                    ["name"] = "Action_10",
                                                                    ["func"] = "ai_reset_atk_interval",
                                                                    ["arg"] = {
                                                                        [1] = 0.5,
                                                                    },
                                                                },
                                                                [2] = {
                                                                    ["type"] = "Action",
                                                                    ["name"] = "return true",
                                                                    ["func"] = "setBlackboard",
                                                                    ["arg"] = {
                                                                        [1] = "runAttactFail",
                                                                        [2] = true,
                                                                    },
                                                                },
                                                            },
                                                            ["type"] = "Sequence",
                                                            ["name"] = "Sequence_10",
                                                            ["func"] = "",
                                                            ["arg"] = {
                                                            },
                                                        },
                                                        [3] = {
                                                            ["children"] = {
                                                                [1] = {
                                                                    ["type"] = "Action",
                                                                    ["name"] = "Action_3",
                                                                    ["func"] = "ai_do_handle",
                                                                    ["arg"] = {
                                                                        [1] = "CMD_Skill",
                                                                    },
                                                                },
                                                                [2] = {
                                                                    ["type"] = "Action",
                                                                    ["name"] = "Action_10",
                                                                    ["func"] = "ai_reset_atk_interval",
                                                                    ["arg"] = {
                                                                        [1] = 1.5,
                                                                    },
                                                                },
                                                            },
                                                            ["type"] = "Sequence",
                                                            ["name"] = "Sequence_3",
                                                            ["func"] = "",
                                                            ["arg"] = {
                                                            },
                                                        },
                                                    },
                                                    ["type"] = "RandomSelector",
                                                    ["name"] = "RandomSelector_1",
                                                    ["func"] = "",
                                                    ["arg"] = {
                                                        [1] = 1,
                                                        [2] = 1,
                                                        [3] = 1,
                                                        [4] = 10,
                                                    },
                                                },
                                            },
                                            ["type"] = "Filter",
                                            ["name"] = "Filter_2",
                                            ["func"] = "ai_is_dis_too_long",
                                            ["arg"] = {
                                                [1] = 300,
                                            },
                                        },
                                        [2] = {
                                            ["children"] = {
                                                [1] = {
                                                    ["children"] = {
                                                        [1] = {
                                                            ["type"] = "Action",
                                                            ["name"] = "Action_1",
                                                            ["func"] = "ai_do_handle",
                                                            ["arg"] = {
                                                                [1] = "CMD_Attack1",
                                                            },
                                                        },
                                                        [2] = {
                                                            ["type"] = "Action",
                                                            ["name"] = "Action_10",
                                                            ["func"] = "ai_reset_atk_interval",
                                                            ["arg"] = {
                                                                [1] = 1,
                                                            },
                                                        },
                                                    },
                                                    ["type"] = "Sequence",
                                                    ["name"] = "Sequence_1",
                                                    ["func"] = "",
                                                    ["arg"] = {
                                                    },
                                                },
                                                [2] = {
                                                    ["children"] = {
                                                        [1] = {
                                                            ["type"] = "Action",
                                                            ["name"] = "Action_2",
                                                            ["func"] = "ai_do_handle",
                                                            ["arg"] = {
                                                                [1] = "CMD_Attack2",
                                                            },
                                                        },
                                                        [2] = {
                                                            ["type"] = "Action",
                                                            ["name"] = "Action_10",
                                                            ["func"] = "ai_reset_atk_interval",
                                                            ["arg"] = {
                                                                [1] = 1,
                                                            },
                                                        },
                                                    },
                                                    ["type"] = "Sequence",
                                                    ["name"] = "Sequence_2",
                                                    ["func"] = "",
                                                    ["arg"] = {
                                                    },
                                                },
                                                [4] = {
                                                    ["children"] = {
                                                        [1] = {
                                                            ["type"] = "Action",
                                                            ["name"] = "Action_10",
                                                            ["func"] = "ai_reset_atk_interval",
                                                            ["arg"] = {
                                                                [1] = 0.5,
                                                            },
                                                        },
                                                        [2] = {
                                                            ["type"] = "Action",
                                                            ["name"] = "return true",
                                                            ["func"] = "setBlackboard",
                                                            ["arg"] = {
                                                                [1] = "runAttactFail",
                                                                [2] = true,
                                                            },
                                                        },
                                                    },
                                                    ["type"] = "Sequence",
                                                    ["name"] = "Sequence_10",
                                                    ["func"] = "",
                                                    ["arg"] = {
                                                    },
                                                },
                                                [3] = {
                                                    ["children"] = {
                                                        [1] = {
                                                            ["type"] = "Action",
                                                            ["name"] = "Action_3",
                                                            ["func"] = "ai_do_handle",
                                                            ["arg"] = {
                                                                [1] = "CMD_Skill",
                                                            },
                                                        },
                                                        [2] = {
                                                            ["type"] = "Action",
                                                            ["name"] = "Action_10",
                                                            ["func"] = "ai_reset_atk_interval",
                                                            ["arg"] = {
                                                                [1] = 1.5,
                                                            },
                                                        },
                                                    },
                                                    ["type"] = "Sequence",
                                                    ["name"] = "Sequence_3",
                                                    ["func"] = "",
                                                    ["arg"] = {
                                                    },
                                                },
                                            },
                                            ["type"] = "RandomSelector",
                                            ["name"] = "RandomSelector_1",
                                            ["func"] = "",
                                            ["arg"] = {
                                                [1] = 3,
                                                [2] = 3,
                                                [3] = 1,
                                                [4] = 3,
                                            },
                                        },
                                    },
                                    ["type"] = "Selector",
                                    ["name"] = "Selector_2",
                                    ["func"] = "",
                                    ["arg"] = {
                                    },
                                },
                            },
                            ["type"] = "Selector",
                            ["name"] = "Selector_1",
                            ["func"] = "",
                            ["arg"] = {
                            },
                        },
                    },
                    ["type"] = "Sequence",
                    ["name"] = "Sequence_1",
                    ["func"] = "",
                    ["arg"] = {
                    },
                },
            },
            ["type"] = "Start",
            ["name"] = "",
            ["arg"] = {
            },
        },
    },
}