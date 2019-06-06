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
                                                            ["name"] = "fa she lei qiu",
                                                            ["func"] = "ai_do_skill1",
                                                            ["arg"] = {
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
                                                    ["name"] = "fa she lei qiu",
                                                    ["func"] = "",
                                                    ["arg"] = {
                                                    },
                                                },
                                                [2] = {
                                                    ["children"] = {
                                                        [1] = {
                                                            ["type"] = "Action",
                                                            ["name"] = "fa she lei zhu",
                                                            ["func"] = "ai_do_skill6",
                                                            ["arg"] = {
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
                                                    ["name"] = "fa she lei zhu",
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
                                                            ["name"] = "shun yi",
                                                            ["func"] = "ai_run_sub_tree",
                                                            ["arg"] = {
                                                                [1] = "shunyi",
                                                                [2] = false,
                                                                [3] = true,
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
                                                    ["name"] = "shun yi",
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
                                                [4] = 5,
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
                                                                    ["name"] = "fa she lei qiu",
                                                                    ["func"] = "ai_do_skill1",
                                                                    ["arg"] = {
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
                                                            ["name"] = "fa she lei qiu",
                                                            ["func"] = "",
                                                            ["arg"] = {
                                                            },
                                                        },
                                                        [2] = {
                                                            ["children"] = {
                                                                [1] = {
                                                                    ["type"] = "Action",
                                                                    ["name"] = "fa she lei zhu",
                                                                    ["func"] = "ai_do_skill6",
                                                                    ["arg"] = {
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
                                                            ["name"] = "fa she lei zhu",
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
                                                                    ["name"] = "shun yi",
                                                                    ["func"] = "ai_run_sub_tree",
                                                                    ["arg"] = {
                                                                        [1] = "shunyi",
                                                                        [2] = false,
                                                                        [3] = true,
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
                                                            ["name"] = "shun yi",
                                                            ["func"] = "",
                                                            ["arg"] = {
                                                            },
                                                        },
                                                    },
                                                    ["type"] = "RandomSelector",
                                                    ["name"] = "RandomSelector_1",
                                                    ["func"] = "",
                                                    ["arg"] = {
                                                        [1] = 2,
                                                        [2] = 2,
                                                        [3] = 2,
                                                        [4] = 5,
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
                                                [2] = {
                                                    ["children"] = {
                                                        [1] = {
                                                            ["type"] = "Action",
                                                            ["name"] = "guang qiu",
                                                            ["func"] = "ai_do_skill3",
                                                            ["arg"] = {
                                                                [1] = 1.5,
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
                                                    ["name"] = "guang qiu",
                                                    ["func"] = "",
                                                    ["arg"] = {
                                                    },
                                                },
                                                [3] = {
                                                    ["children"] = {
                                                        [1] = {
                                                            ["type"] = "Action",
                                                            ["name"] = "fa she lei qiu",
                                                            ["func"] = "ai_do_skill1",
                                                            ["arg"] = {
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
                                                    ["name"] = "fa she lei qiu",
                                                    ["func"] = "",
                                                    ["arg"] = {
                                                    },
                                                },
                                                [1] = {
                                                    ["children"] = {
                                                        [1] = {
                                                            ["type"] = "Action",
                                                            ["name"] = "lei quan",
                                                            ["func"] = "ai_do_skill2",
                                                            ["arg"] = {
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
                                                    ["name"] = "lei quan",
                                                    ["func"] = "",
                                                    ["arg"] = {
                                                    },
                                                },
                                                [4] = {
                                                    ["children"] = {
                                                        [1] = {
                                                            ["type"] = "Action",
                                                            ["name"] = "fa she lei zhu",
                                                            ["func"] = "ai_do_skill6",
                                                            ["arg"] = {
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
                                                    ["name"] = "fa she lei zhu",
                                                    ["func"] = "",
                                                    ["arg"] = {
                                                    },
                                                },
                                                [5] = {
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
                                            },
                                            ["type"] = "RandomSelector",
                                            ["name"] = "RandomSelector_1",
                                            ["func"] = "",
                                            ["arg"] = {
                                                [1] = 4,
                                                [2] = 4,
                                                [3] = 1,
                                                [4] = 1,
                                                [5] = 4,
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